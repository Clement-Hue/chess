#include "pch.h"
#include "game/BoardGame.h"
#include "game/Piece.h"
#include "Piece.mock.h"

TEST(KnightSquareAvailableTest, all_squares_free)
{
	BoardGame board;
	Knight knight{ board, board[35], std::make_unique<WhiteColor>() };
	knight.compute_pseudo_legal_squares();
	const auto& bishop_eligible_squares = knight.get_legal_squares();
	EXPECT_EQ(std::count(bishop_eligible_squares.begin(), bishop_eligible_squares.end(), nullptr), 56);
	EXPECT_THAT(bishop_eligible_squares, IsSupersetOf({
		&board[18], &board[20], &board[25], &board[29], &board[41],
		&board[45], &board[50], &board[52], 
	}));
}


TEST(KnightSquareAvailableTest, squares_taken_by_friends)
{
	BoardGame board;
	Knight knight{ board, board[35], std::make_unique<WhiteColor>() };
	MockPiece p1{ board, board[18], std::make_unique<WhiteColor>() };
	MockPiece p2{ board, board[50], std::make_unique<WhiteColor>() };
	knight.compute_pseudo_legal_squares();
	const auto& bishop_eligible_squares = knight.get_legal_squares();
	EXPECT_EQ(std::count(bishop_eligible_squares.begin(), bishop_eligible_squares.end(), nullptr), 58);
	EXPECT_THAT(bishop_eligible_squares, IsSupersetOf({
		&board[20], &board[25], &board[29], &board[41],
		&board[45], &board[52], 
	}));
}

