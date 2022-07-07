#include "Piece.h"
#include "Constants.h"


Piece::Piece(BoardGame& board, Square& square): board_(board), square_(&square)
{
	this->square_->piece = this;
}

void Piece::move(Square& square) noexcept
{
	this->square_->piece = nullptr;
	this->square_ = &square;
	this->square_->piece = this;
}

std::vector<Square*> Rock::available_square() const noexcept
{
	std::vector<Square*> squares;
	const uint8_t column = this->square_->value % NB_SQUARES_BY_ROW;
	const uint8_t row = this->square_->value / 8;
	for (uint8_t i = 0; i<NB_SQUARES; ++i)
	{
		if (i == this->square_->value) continue;
		if (i % 8 == column || i / 8 == row) squares.emplace_back(&this->board_[i]);
	}
	return squares;
}
