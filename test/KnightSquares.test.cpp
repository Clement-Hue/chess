#include "pch.h"
#include "game/BoardGame.h"
#include "game/Piece.h"
#include "Piece.mock.h"

TEST(KnightSquareAvailableTest, all_squares_free)
{
	BoardGame board;
	auto& knight = board.get_color(0).add_piece<Knight>(board[35]);
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
	auto& knight = board.get_color(0).add_piece<Knight>(board[35]);
	board.get_color(0).add_piece<MockPiece>(board[18]);
	board.get_color(0).add_piece<MockPiece>(board[50]);
	knight.compute_pseudo_legal_squares();
	const auto& bishop_eligible_squares = knight.get_legal_squares();
	EXPECT_EQ(std::count(bishop_eligible_squares.begin(), bishop_eligible_squares.end(), nullptr), 58);
	EXPECT_THAT(bishop_eligible_squares, IsSupersetOf({
		&board[20], &board[25], &board[29], &board[41],
		&board[45], &board[52], 
	}));
}

