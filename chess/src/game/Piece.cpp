#include "Piece.h"
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

void Piece::compute_legal_squares() noexcept
{
	this->filter_legal_squares_if_pinned();
}

void Piece::move(Square& square) noexcept
{
	if (!this->get_color().is_turn()) return;
	if (!this->legal_squares_[square.get_value()]) return;
	const auto piece_on_square = square.get_piece();
	if (piece_on_square && piece_on_square->is_friend_of(*this)) return;
	if (piece_on_square && piece_on_square->is_enemy_of(*this))
	{
		piece_on_square->remove_square();
	}
	this->square_->remove_piece();
	this->square_ = &square;
	this->square_->set_piece(*this);
	this->has_moved_ = true;
	printf("piece has moved to %d\n", this->square_->get_value());
	this->color_.get_board().next_turn();
}

void Rock::compute_pseudo_legal_squares() noexcept
{
	linear_pseudo_legal_squares::add_rank_squares(*this, this->color_.get_board());
	linear_pseudo_legal_squares::add_file_squares(*this, this->color_.get_board());
}

void Bishop::compute_pseudo_legal_squares() noexcept
{
	linear_pseudo_legal_squares::add_diagonal_squares(*this, this->color_.get_board());
	linear_pseudo_legal_squares::add_anti_diagonal_squares(*this, this->color_.get_board());
}

void Queen::compute_pseudo_legal_squares() noexcept
{
	linear_pseudo_legal_squares::add_rank_squares(*this, this->color_.get_board());
	linear_pseudo_legal_squares::add_file_squares(*this, this->color_.get_board());
	linear_pseudo_legal_squares::add_diagonal_squares(*this, this->color_.get_board());
	linear_pseudo_legal_squares::add_anti_diagonal_squares(*this, this->color_.get_board());
}

void King::compute_pseudo_legal_squares() noexcept
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
			this->legal_squares_[square_it->get_value()] = &*square_it;
		}
	}
}

/**
 * Remove from legal squares list the squares that are attacked by enemy pieces
 */
void King::compute_legal_squares() noexcept
{
	Piece::compute_legal_squares();
	for (const auto& color: this->color_.get_board().get_colors())
	{
		if (*color == this->get_color()) continue;
		for (const auto& piece: color->get_pieces())
		{
			for (const auto& square: piece->get_legal_squares())
			{
				if (!square) continue;
				this->legal_squares_[square->get_value()] = nullptr;
			}
		}
	}
}

template<typename It1, typename It2>
void Knight::add_eligible_squares() noexcept
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
			this->legal_squares_[it_2->get_value()] = &*it_2;
		}
	}
}


void Knight::compute_pseudo_legal_squares() noexcept
{
	this->add_eligible_squares<FileIterator, RankIterator>();
	this->add_eligible_squares<RankIterator, FileIterator>();
}

void Pawn::compute_pseudo_legal_squares() noexcept
{
	this->get_color().accept(PawnPseudoLegalSquares(*this));
}

void Pawn::compute_legal_squares() noexcept 
{
	Piece::compute_legal_squares();
	this->get_color().accept(PawnLegalSquares(*this));
}


bool Pawn::has_moved() const noexcept
{
	return this->square_->get_rank() != this->color_.get_rank().second;
}
