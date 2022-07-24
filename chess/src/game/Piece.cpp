#include "Piece.h"
#include "BoardGame.h"
#include "LinearEligibleMove.h"


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
	BoardIterator iterators[8] = {
		++RankIterator(this->board_).begin(*this->square_), --RankIterator(this->board_).begin(*this->square_),
		++FileIterator(this->board_).begin(*this->square_), --FileIterator(this->board_).begin(*this->square_),
		++DiagonalIterator(this->board_).begin(*this->square_), --DiagonalIterator(this->board_).begin(*this->square_),
		++AntiDiagonalIterator(this->board_).begin(*this->square_), --AntiDiagonalIterator(this->board_).begin (*this->square_)
	};
	for (const auto& square_it: iterators)
	{
		if ( square_it && !square_it->has_friend_piece_of(*this) )
		{
			this->eligible_squares_[square_it->get_value()] = &*square_it;
		}
	}
}

void Knight::compute_eligible_squares() noexcept
{
}

void Pawn::compute_eligible_squares() noexcept
{
}
