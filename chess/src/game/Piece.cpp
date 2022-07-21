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
	constexpr int8_t diag_offset = NB_SQUARES_BY_ROW - 1;
	constexpr int8_t antidiag_offset = NB_SQUARES_BY_ROW + 1;
	constexpr int8_t offsets[8] = { 1, -1,diag_offset, -diag_offset, antidiag_offset, -antidiag_offset,
	NB_SQUARES_BY_ROW, -NB_SQUARES_BY_ROW };
	for (const auto offset : offsets)
	{
		const int8_t square_value = this->square_->get_value() + offset;
		if (!this->board_.has_square_value(square_value)) continue;
		if (this->board_[square_value].is_free() || this->board_[square_value].has_enemy_piece_of(*this))
		{
			this->eligible_squares_[square_value] =  &this->board_[square_value];
		}
	}
}

void Knight::compute_eligible_squares() noexcept
{
}

void Pawn::compute_eligible_squares() noexcept
{
}
