#include "Piece.h"
#include "Move.h"
#include "BoardGame.h"
#include "BoardIterator.h"
#include "LinearMoves.h"
#include "PieceColor.h"
#include "PawnMoves.h"


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

void Piece::clear_legal_moves() noexcept
{
	for (auto& square: this->legal_moves_)
	{
		square = nullptr;
	}
}


/*
 * Clear all legal moves except the array of squares values pass as parameter
 */
void Piece::clear_legal_moves_except(const std::vector<int8_t>& squares_values) noexcept
{
	for (int8_t i = 0; i< this->legal_moves_.size(); ++i)
	{
		if (std::find(squares_values.begin(), squares_values.end(), i 
			) == squares_values.end())
		{
			this->legal_moves_[i] = nullptr;
		} 
	}
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

void Rock::compute_legal_moves() noexcept
{
	linear_moves::add_rank_moves(*this, this->color_.get_board());
	linear_moves::add_file_moves(*this, this->color_.get_board());
}

void Rock::remove_illegal_moves_of_enemy(PieceColor& enemy_color) noexcept
{
	linear_moves::remove_illegal_rank_moves(*this, this->color_.get_board(), enemy_color);
	linear_moves::remove_illegal_file_moves(*this, this->color_.get_board(), enemy_color);
}

bool Rock::is_on_start() const noexcept
{
	return this->color_.get_rank().first == this->square_->get_rank() && (
		this->square_->get_file() == 0 || this->square_->get_file() == NB_COLUMNS - 1
		);
}

void Bishop::compute_legal_moves() noexcept
{
	linear_moves::add_diagonal_moves(*this, this->color_.get_board());
	linear_moves::add_anti_diagonal_moves(*this, this->color_.get_board());
}

void Bishop::remove_illegal_moves_of_enemy(PieceColor& enemy_color) noexcept
{
	linear_moves::remove_illegal_diagonal_moves(*this, this->color_.get_board(), enemy_color);
	linear_moves::remove_illegal_anti_diagonal_moves(*this, this->color_.get_board(), enemy_color);
}

bool Bishop::is_on_start() const noexcept
{
	return this->color_.get_rank().first == this->square_->get_rank() && (
		this->square_->get_file() == 2 || this->square_->get_file() == NB_COLUMNS - 3
		);
}

void Queen::compute_legal_moves() noexcept
{
	linear_moves::add_rank_moves(*this, this->color_.get_board());
	linear_moves::add_file_moves(*this, this->color_.get_board());
	linear_moves::add_diagonal_moves(*this, this->color_.get_board());
	linear_moves::add_anti_diagonal_moves(*this, this->color_.get_board());
}

void Queen::remove_illegal_moves_of_enemy(PieceColor& enemy_color) noexcept
{
	linear_moves::remove_illegal_rank_moves(*this, this->color_.get_board(), enemy_color);
	linear_moves::remove_illegal_file_moves(*this, this->color_.get_board(), enemy_color);
	linear_moves::remove_illegal_diagonal_moves(*this, this->color_.get_board(), enemy_color);
	linear_moves::remove_illegal_anti_diagonal_moves(*this, this->color_.get_board(), enemy_color);
}

bool Queen::is_on_start() const noexcept
{
	return this->color_.get_rank().first == this->square_->get_rank() && 
		this->square_->get_file() == 3 ;
}

template <typename Fn>
void King::legal_squares(const Fn& legal_squares_fn) noexcept
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
			legal_squares_fn(square_it);
		}
	}
}

void King::compute_legal_moves() noexcept
{
	this->legal_squares([this](const BoardIterator& it)
	{
		this->legal_moves_[it->get_value()] = std::make_unique<SimpleMove>();
	});
	this->add_long_castle_if_possible();
	this->add_short_castle_if_possible();
}

void King::remove_illegal_moves_of_enemy(PieceColor& enemy_color) noexcept
{
	const auto& king = enemy_color.get_king();
	this->legal_squares([&king](const BoardIterator& it)
	{
		if (king)
		{
			king->get_legal_move(it->get_value()) = nullptr;
		}
	});
}

bool King::is_on_start() const noexcept
{
	return this->color_.get_rank().first == this->square_->get_rank() && 
		this->square_->get_file() == 4 ;
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


template<typename It1, typename It2, typename Fn>
void Knight::legal_squares(const Fn& legal_square_fn) noexcept
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
			legal_square_fn(it_2);
		}
	}
}


void Knight::compute_legal_moves() noexcept
{
	const auto& add_move = [this](const BoardIterator& square_it)
	{
		this->legal_moves_[square_it->get_value()] = std::make_unique<SimpleMove>();
	};
	this->legal_squares<FileIterator, RankIterator>(add_move);
	this->legal_squares<RankIterator, FileIterator>(add_move);
}

void Knight::remove_illegal_moves_of_enemy(PieceColor& enemy_color) noexcept
{
	const auto& king = enemy_color.get_king();
	const auto& remove_illegal_king_moves = [&king, this, &enemy_color](const BoardIterator& square_it)
	{
		if (!king) return;
		if (square_it->get_piece() == king)
		{
			enemy_color.clear_legal_moves_except({this->square_->get_value()});
		}
		king->get_legal_move(square_it->get_value()) = nullptr;
	};
	this->legal_squares<FileIterator, RankIterator>(remove_illegal_king_moves);
	this->legal_squares<RankIterator, FileIterator>(remove_illegal_king_moves);
}

bool Knight::is_on_start() const noexcept
{
	return this->color_.get_rank().first == this->square_->get_rank() && (
		this->square_->get_file() == 1 || this->square_->get_file() == NB_COLUMNS - 2
		);
}


void Pawn::compute_legal_moves() noexcept 
{
	this->get_color().accept(PawnLegalMoves(*this));
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

void Pawn::clear_legal_moves() noexcept
{
	Piece::clear_legal_moves();
	if (this->color_.is_turn())
	{
		this->has_double_moved_ = false;
	}
}

void Pawn::remove_illegal_moves_of_enemy(PieceColor& enemy_color) noexcept
{
	this->get_color().accept(RemoveIllegalMoves(*this, enemy_color));
}
