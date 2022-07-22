#include "Piece.h"
#include "BoardGame.h"
#include "Constants.h"
#include "EligibleMove.h"


Piece::Piece(BoardGame& board, Square& square, const PieceColor color): board_(board), square_(&square),
                                                                        color_(color)	
{
	this->square_->set_piece(*this);
}

void Piece::move(Square& square) noexcept
{
	const auto piece_on_square = square.get_piece();
	if (piece_on_square && piece_on_square->is_friend_of(*this)) return;
	if (piece_on_square && piece_on_square->is_enemy_of(*this))
	{
		piece_on_square->remove_square();
	}
	this->square_->remove_piece();
	this->square_ = &square;
	this->square_->set_piece(*this);
}

void Rock::compute_eligible_squares() noexcept
{
	RankEligibleMove(this->board_, *this)();
	FileEligibleMove(this->board_, *this)();
}

void Bishop::compute_eligible_squares() noexcept
{
	DiagonalEligibleMove(this->board_, *this)();
	AntiDiagonalEligibleMove(this->board_, *this)();
}

void Queen::compute_eligible_squares() noexcept
{
	RankEligibleMove(this->board_, *this)();
	FileEligibleMove(this->board_, *this)();
	DiagonalEligibleMove(this->board_, *this)();
	AntiDiagonalEligibleMove(this->board_, *this)();
}

void King::compute_eligible_squares() noexcept
{
	if (const auto& square_it = ++this->board_.rank_it(*this->square_))
	{
		this->eligible_squares_[square_it->get_value()] = *square_it;
	}
	if (const auto& square_it = --this->board_.rank_it(*this->square_))
	{
		this->eligible_squares_[square_it->get_value()] = *square_it;
	}
	if (const auto& square_it = ++this->board_.file_it(*this->square_))
	{
		this->eligible_squares_[square_it->get_value()] = *square_it;
	}
	if (const auto& square_it = --this->board_.file_it(*this->square_))
	{
		this->eligible_squares_[square_it->get_value()] = *square_it;
	}
	if (const auto& square_it = ++this->board_.diagonal_it(*this->square_))
	{
		this->eligible_squares_[square_it->get_value()] = *square_it;
	}
	if (const auto& square_it = --this->board_.diagonal_it(*this->square_))
	{
		this->eligible_squares_[square_it->get_value()] = *square_it;
	}
	if (const auto& square_it = ++this->board_.anti_diagonal_it(*this->square_)) 
	{
		this->eligible_squares_[square_it->get_value()] = *square_it;
	}
	if (const auto& square_it = --this->board_.anti_diagonal_it(*this->square_))
	{
		this->eligible_squares_[square_it->get_value()] = *square_it;
	}
}

void Knight::compute_eligible_squares() noexcept
{
}

void Pawn::compute_eligible_squares() noexcept
{
}
