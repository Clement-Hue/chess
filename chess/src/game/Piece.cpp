#include "Piece.h"
#include "Application.h"
#include "Constants.h"


void Piece::move(Square& square) noexcept
{
	this->square_ = square;
	square.piece = this;
}

std::vector<uint8_t> Rock::available_square() const noexcept
{
	std::vector<uint8_t> squares;
	const uint8_t column = this->square_.value % NB_SQUARES_BY_ROW;
	const uint8_t row = this->square_.value / 8;
	for (uint8_t i = 0; i<NB_SQUARES; ++i)
	{
		if (i == this->square_.value) continue;
		if (i % 8 == column || i / 8 == row) squares.emplace_back(i);
	}
	return squares;
}
