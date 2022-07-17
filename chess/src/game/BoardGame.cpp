#include "BoardGame.h"
#include "Constants.h"
#include "Piece.h"

static std::vector<Square> create_squares()
{
	std::vector<Square> squares;
	squares.reserve(NB_SQUARES);
	for (uint8_t i = 0; i<NB_SQUARES; i++)
	{
		squares.emplace_back(Square{ i });
	}
	return squares;
}

BoardGame::BoardGame(): squares_(create_squares())
{
}

void BoardGame::init_valuable_pieces(PieceColor color, const uint8_t offset) noexcept
{
	auto& pieces = this->pieces_(color);
	pieces.emplace_back(
		std::make_unique<Rock>( *this, this->squares_[offset], color)
	);
	pieces.emplace_back(
		std::make_unique<Knight>( *this, this->squares_[offset + 1], color)
	);
	pieces.emplace_back(
		std::make_unique<Bishop>( *this, this->squares_[offset + 2], color)
	);
	pieces.emplace_back(
		std::make_unique<Queen>( *this, this->squares_[offset + 3], color)
	);
	pieces.emplace_back(
		std::make_unique<King>( *this, this->squares_[offset + 4], color)
	);
	pieces.emplace_back(
		std::make_unique<Bishop>( *this, this->squares_[offset + 5], color)
	);
	pieces.emplace_back(
		std::make_unique<Knight>( *this, this->squares_[offset + 6], color)
	);
	pieces.emplace_back(
		std::make_unique<Rock>( *this, this->squares_[offset + 7], color)
	);
}

void BoardGame::init_pawns(PieceColor color, const uint8_t offset) noexcept
{
	auto& pieces = this->pieces_(color);
	for (uint8_t i = offset; i<offset+NB_SQUARES_BY_ROW; ++i)
	{
		pieces.emplace_back(
			std::make_unique<Pawn>( *this, this->squares_[i], color)
		);
	}
}


void BoardGame::init_game() noexcept
{
	this->init_valuable_pieces(PieceColor::black, 0);
	this->init_valuable_pieces(PieceColor::white, NB_SQUARES - NB_SQUARES_BY_ROW   );
	this->init_pawns(PieceColor::black, 8);
	this->init_pawns(PieceColor::white, 48);
}


