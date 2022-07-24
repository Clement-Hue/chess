#include "BoardGame.h"
#include "Constants.h"
#include "Piece.h"

static std::vector<Square> create_squares()
{
	std::vector<Square> squares;
	squares.reserve(NB_SQUARES);
	for (int8_t i = 0; i<NB_SQUARES; i++)
	{
		squares.emplace_back(Square{ i });
	}
	return squares;
}

BoardGame::BoardGame(): squares_(create_squares())
{
}

template <typename Color>
void BoardGame::init_valuable_pieces() noexcept
{
	auto& pieces = this->get_pieces<Color>();
	const auto offset = Color::first_rank * NB_SQUARES_BY_ROW;
	pieces.emplace_back(
		std::make_unique<Rock>( *this, this->squares_[offset], std::make_unique<Color>())
	);
	pieces.emplace_back(
		std::make_unique<Knight>( *this, this->squares_[offset + 1], std::make_unique<Color>())
	);
	pieces.emplace_back(
		std::make_unique<Bishop>( *this, this->squares_[offset + 2], std::make_unique<Color>())
	);
	pieces.emplace_back(
		std::make_unique<Queen>( *this, this->squares_[offset + 3], std::make_unique<Color>())
	);
	pieces.emplace_back(
		std::make_unique<King>( *this, this->squares_[offset + 4], std::make_unique<Color>())
	);
	pieces.emplace_back(
		std::make_unique<Bishop>( *this, this->squares_[offset + 5], std::make_unique<Color>())
	);
	pieces.emplace_back(
		std::make_unique<Knight>( *this, this->squares_[offset + 6], std::make_unique<Color>())
	);
	pieces.emplace_back(
		std::make_unique<Rock>(*this, this->squares_[offset + 7], std::make_unique<Color>())
	);
}

template <typename Color>
void BoardGame::init_pawns() noexcept
{
	auto& pieces = this->get_pieces<Color>();
	const auto offset = Color::second_rank * NB_SQUARES_BY_ROW;
	for (uint8_t i = offset; i<offset+NB_SQUARES_BY_ROW; ++i)
	{
		pieces.emplace_back(
			std::make_unique<Pawn>( *this, this->squares_[i], std::make_unique<Color>())
		);
	}
}


void BoardGame::init_game() noexcept
{
	this->init_valuable_pieces<BlackColor>();
	this->init_valuable_pieces<WhiteColor>();
	this->init_pawns<BlackColor>();
	this->init_pawns<WhiteColor>();
}


