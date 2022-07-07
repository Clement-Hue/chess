#define BOOST_TEST_MODULE AvailableMove
#include <boost/test/included/unit_test.hpp>
#include "game/Piece.h"
#include "game/BoardGame.h"
#include <vector>

BOOST_AUTO_TEST_CASE(AvailableRockMove)
{
	Square square{ 2 };
	const BoardGame board;
	const Rock rock{ board, square };
	std::vector<uint8_t> available_square = { 0,1,3,4,5,6,7,
		10, 18, 26, 34, 42, 50, 58
	};
	const auto result =  rock.available_square();
	BOOST_CHECK_EQUAL_COLLECTIONS(available_square.begin(), available_square.end(),
		result.begin(), result.end());
}