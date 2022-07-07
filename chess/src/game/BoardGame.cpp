#include "BoardGame.h"
#include "Constants.h"


static std::vector<Square> build_squares()
{
	std::vector<Square> squares;
	squares.reserve(NB_SQUARES);
	for (uint8_t i = 0; i<NB_SQUARES; ++i)
	{
		squares.emplace_back(Square{ i });
	}
	return squares;
}

BoardGame::BoardGame()
{
	this->squares_ = build_squares();
}
