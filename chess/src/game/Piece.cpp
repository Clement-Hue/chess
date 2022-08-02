#include "Piece.h"
#include "Move.h"
#include "BoardGame.h"
#include "BoardIterator.h"
#include "LinearLegalSquares.h"
#include "PieceColor.h"
#include "PawnLegalSquares.h"


Piece::Piece(Square* square, PieceColor& color): square_(square), color_(color)
{
	this->square_->set_piece(*this);
}

bool Piece::is_enemy_of(const Piece& piece) const noexcept
{
	return this->get_color() != piece.get_color(); 
}

bool Piece::is_friend_of(const Piece& piece) const noexcept
{
	return !this->is_enemy_of(piece);
}

std::vector<Square*> Piece::get_squares_of_legal_moves() const noexcept
{
	std::vector<Square*> square_list;
	for (int8_t i = 0 ;i < this->legal_moves_.size(); ++i)
	{
		if (this->legal_moves_[i])
		{
			square_list.emplace_back(&this->color_.get_board()[i]);
		}
	}
	return square_list;
}

void Piece::clear_legal_moves_states() noexcept
{
	for (auto& square: this->legal_moves_)
	{
		square = nullptr;
	}
	this->pinning_filter_ = nullptr;
}

void Piece::compute_legal_moves() noexcept
{
	this->filter_legal_moves_if_pinned();
}

bool Piece::move(Square& square) noexcept
{
	if (!this->get_color().is_turn()) return false;
	if (!this->legal_moves_[square.get_value()]) return false;
	if ((*this->legal_moves_[square.get_value()])(*this, square))
	{
		this->color_.get_board().next_turn();
		return true;
	}
	return false;
}

void Rock::compute_pseudo_legal_moves() noexcept
{
	linear_pseudo_legal_squares::add_rank_squares(*this, this->color_.get_board());
	linear_pseudo_legal_squares::add_file_squares(*this, this->color_.get_board());
}

bool Rock::is_on_start() const noexcept
{
	return this->color_.get_rank().first == this->square_->get_rank() && (
		this->square_->get_file() == 0 || this->square_->get_file() == NB_COLUMNS - 1
		);
}

void Bishop::compute_pseudo_legal_moves() noexcept
{
	linear_pseudo_legal_squares::add_diagonal_squares(*this, this->color_.get_board());
	linear_pseudo_legal_squares::add_anti_diagonal_squares(*this, this->color_.get_board());
}

bool Bishop::is_on_start() const noexcept
{
	return this->color_.get_rank().first == this->square_->get_rank() && (
		this->square_->get_file() == 2 || this->square_->get_file() == NB_COLUMNS - 3
		);
}

void Queen::compute_pseudo_legal_moves() noexcept
{
	linear_pseudo_legal_squares::add_rank_squares(*this, this->color_.get_board());
	linear_pseudo_legal_squares::add_file_squares(*this, this->color_.get_board());
	linear_pseudo_legal_squares::add_diagonal_squares(*this, this->color_.get_board());
	linear_pseudo_legal_squares::add_anti_diagonal_squares(*this, this->color_.get_board());
}

bool Queen::is_on_start() const noexcept
{
	return this->color_.get_rank().first == this->square_->get_rank() && 
		this->square_->get_file() == 3 ;
}

void King::compute_pseudo_legal_moves() noexcept
{
	BoardIterator iterators[8] = {
		++RankIterator(this->color_.get_board()).begin(*this->square_), --RankIterator(this->color_.get_board()).begin(*this->square_),
		++FileIterator(this->color_.get_board()).begin(*this->square_), --FileIterator(this->color_.get_board()).begin(*this->square_),
		++DiagonalIterator(this->color_.get_board()).begin(*this->square_), --DiagonalIterator(this->color_.get_board()).begin(*this->square_),
		++AntiDiagonalIterator(this->color_.get_board()).begin(*this->square_), --AntiDiagonalIterator(this->color_.get_board()).begin (*this->square_)
	};
	for (const auto& square_it: iterators)
	{
		if ( square_it && !square_it->has_friend_piece_of(*this) )
		{
			this->legal_moves_[square_it->get_value()] = std::make_unique<SimpleMove>();
		}
	}
}

void King::compute_legal_moves() noexcept
{
	Piece::compute_legal_moves();
	this->remove_attacked_squares();
	this->add_long_castle_if_possible();
	this->add_short_castle_if_possible();
}

bool King::is_on_start() const noexcept
{
	return this->color_.get_rank().first == this->square_->get_rank() && 
		this->square_->get_file() == 4 ;
}

/**
 * Remove from legal moves list the squares that are attacked by enemy pieces
 */
void King::remove_attacked_squares() noexcept
{
	for (const auto& color: this->color_.get_board().get_colors())
	{
		if (*color == this->get_color()) continue;
		for (const auto& piece: color->get_pieces())
		{
			for (int8_t i = 0 ;i < piece->get_legal_moves().size(); ++i)
			{
				if (!piece->get_legal_move(i)) continue;
				this->legal_moves_[i] = nullptr;
			}
		}
	}
}

void King::add_castling_move(const increment_fn_type increment_fn) noexcept
{
	if (this->has_moved_ || !this->is_on_start()) return;
	int8_t i = 0;
	Square* rock_square{ nullptr };
	Square* king_square{ nullptr };
	for ( auto& it = RankIterator(this->color_.get_board()).begin(*this->square_)
		;it; increment_fn(it))
	{
		if (i <= 2 && this->color_.is_square_attacked(*it)) return;
		if (i == 1) rock_square = &*it;
		if (i == 2) king_square = &*it;
		if (Piece* const piece = it->get_piece(); piece && piece != this)
		{
			if (dynamic_cast<Rock*>(piece) && piece->is_friend_of(*this) && !piece->has_moved() && piece->is_on_start()
				&& king_square && rock_square)
			{
				this->legal_moves_[it->get_value()] = std::make_unique<CastleMove>(*piece, *king_square, *rock_square);
			}
			return;
		}
		++i;
	}
}



template<typename It1, typename It2>
void Knight::add_legal_moves() noexcept
{
	BoardIterator first_it[2] = {
		It1(this->color_.get_board()).begin(*this->get_square())+=2,
		It1(this->color_.get_board()).begin(*this->get_square())-=2,
	};
	for (const auto& it_1 : first_it)
	{
		if (!it_1) continue;
		BoardIterator second_it[2] = {
			It2(this->color_.get_board()).begin(*it_1)+=1,
			It2(this->color_.get_board()).begin(*it_1)-=1,
		};
		for (const auto& it_2: second_it)
		{
			if (!it_2 || it_2->has_friend_piece_of(*this)) continue;
			this->legal_moves_[it_2->get_value()] = std::make_unique<SimpleMove>();
		}
	}
}


void Knight::compute_pseudo_legal_moves() noexcept
{
	this->add_legal_moves<FileIterator, RankIterator>();
	this->add_legal_moves<RankIterator, FileIterator>();
}

bool Knight::is_on_start() const noexcept
{
	return this->color_.get_rank().first == this->square_->get_rank() && (
		this->square_->get_file() == 1 || this->square_->get_file() == NB_COLUMNS - 2
		);
}

void Pawn::compute_pseudo_legal_moves() noexcept
{
	this->get_color().accept(PawnPseudoLegalSquares(*this));
}

void Pawn::compute_legal_moves() noexcept 
{
	Piece::compute_legal_moves();
	this->get_color().accept(PawnLegalSquares(*this));
}


bool Pawn::is_on_start() const noexcept
{
	return this->square_->get_rank() == this->color_.get_rank().second;
}

void Pawn::add_move(const Square& square) noexcept
{
	if (square.get_rank() == 0 || square.get_rank() == NB_ROWS -1)
	{
		this->legal_moves_[square.get_value()] = std::make_unique<PromoteMove>(this->color_);
		return;
	}
	if (abs(square.get_rank() - this->square_->get_rank()) == 2)
	{
		this->legal_moves_[square.get_value()] = std::make_unique<PawnDoubleMove>();
		return;
	}
	this->legal_moves_[square.get_value()] = std::make_unique<SimpleMove>();
}

void Pawn::clear_legal_moves_states() noexcept
{
	Piece::clear_legal_moves_states();
	if (this->color_.is_turn())
	{
		this->has_double_moved_ = false;
	}
}
