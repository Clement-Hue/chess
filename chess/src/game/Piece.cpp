#include "Piece.h"
#include "BoardGame.h"
#include "Constants.h"
#include "LineMove.h"


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

Piece::e_squares_type Piece::get_eligible_squares() const noexcept 
{
	auto squares = this->get_natural_eligible_squares();
	if (this->pinned) 
	{
		this->pinned(squares);
	}
	return squares;
}


Piece::e_squares_type Rock::get_natural_eligible_squares() const noexcept
{
	e_squares_type squares{};
	ForthFileMove(this->board_, *this).add_eligible_squares(squares);
	BackFileMove(this->board_, *this).add_eligible_squares(squares);
	ForthRankMove(this->board_, *this).add_eligible_squares(squares);
	BackRankMove(this->board_, *this).add_eligible_squares(squares);
	return squares;
}

Piece::e_squares_type Bishop::get_natural_eligible_squares() const noexcept
{
	e_squares_type squares{};
	ForthDiagonalMove(this->board_, *this).add_eligible_squares(squares);
	BackDiagonalMove(this->board_, *this).add_eligible_squares(squares);
	ForthAntiDiagonalMove(this->board_, *this).add_eligible_squares(squares);
	BackAntiDiagonalMove(this->board_, *this).add_eligible_squares(squares);
	return squares;
}

Piece::e_squares_type Queen::get_natural_eligible_squares() const noexcept
{
	e_squares_type squares{};
	ForthFileMove(this->board_, *this).add_eligible_squares(squares);
	BackFileMove(this->board_, *this).add_eligible_squares(squares);
	ForthRankMove(this->board_, *this).add_eligible_squares(squares);
	BackRankMove(this->board_, *this).add_eligible_squares(squares);
	ForthDiagonalMove(this->board_, *this).add_eligible_squares(squares);
	BackDiagonalMove(this->board_, *this).add_eligible_squares(squares);
	ForthAntiDiagonalMove(this->board_, *this).add_eligible_squares(squares);
	BackAntiDiagonalMove(this->board_, *this).add_eligible_squares(squares);
	return squares;
}

Piece::e_squares_type King::get_natural_eligible_squares() const noexcept
{
	e_squares_type squares{};
	constexpr int8_t diag_offset = NB_SQUARES_BY_ROW - 1;
	constexpr int8_t antidiag_offset = NB_SQUARES_BY_ROW + 1;
	constexpr int8_t offsets[8] = { 1, -1,diag_offset, -diag_offset, antidiag_offset, -antidiag_offset,
	NB_SQUARES_BY_ROW, -NB_SQUARES_BY_ROW };
	for (const auto offset : offsets)
	{
		const uint8_t square_value = this->square_->get_value() + offset;
		if (!this->board_.has_square_value(square_value)) continue;
		if (this->board_[square_value].is_free() || this->board_[square_value].has_enemy_piece_of(*this))
		{
			squares[square_value] =  &this->board_[square_value];
		}
	}
	return squares;
}

Piece::e_squares_type Knight::get_natural_eligible_squares() const noexcept
{
	return std::array<Square*, NB_SQUARES>();
}

Piece::e_squares_type Pawn::get_natural_eligible_squares() const noexcept
{
	return std::array<Square*, NB_SQUARES>();
}
