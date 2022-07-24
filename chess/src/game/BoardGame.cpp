#include "BoardGame.h"
#include "Constants.h"
#include "Piece.h"
#include "BoardIterator.h"

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
	constexpr auto init_square_value = Color::first_rank * NB_SQUARES_BY_ROW;
	auto square_it = RankIterator(*this).begin(this->squares_[init_square_value]);
	pieces.emplace_back(
		std::make_unique<Rock>( *this, *square_it, std::make_unique<Color>())
	);
	pieces.emplace_back(
		std::make_unique<Knight>( *this, *++square_it, std::make_unique<Color>())
	);
	pieces.emplace_back(
		std::make_unique<Bishop>( *this, *++square_it, std::make_unique<Color>())
	);
	pieces.emplace_back(
		std::make_unique<Queen>( *this, *++square_it, std::make_unique<Color>())
	);
	pieces.emplace_back(
		std::make_unique<King>( *this, *++square_it, std::make_unique<Color>())
	);
	pieces.emplace_back(
		std::make_unique<Bishop>( *this, *++square_it, std::make_unique<Color>())
	);
	pieces.emplace_back(
		std::make_unique<Knight>( *this, *++square_it, std::make_unique<Color>())
	);
	pieces.emplace_back(
		std::make_unique<Rock>( *this, *++square_it, std::make_unique<Color>())
	);
}

template <typename Color>
void BoardGame::init_pawns() noexcept
{
	auto& pieces = this->get_pieces<Color>();
	constexpr auto init_square_value = Color::second_rank * NB_SQUARES_BY_ROW;
	for (auto& square_it = RankIterator(*this).begin(this->squares_[init_square_value]); 
		square_it; ++square_it)
	{
		pieces.emplace_back(
			std::make_unique<Pawn>( *this, *square_it, std::make_unique<Color>())
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


