#include "pch.h"
#include "game/BoardGame.h"
#include "game/Piece.h"

TEST(PawnSquareAvailableTest, white_pawn_in_middle_of_board)
{
	BoardGame board;
	Pawn pawn{ board, board[24], std::make_unique<WhiteColor>() };
	pawn.compute_eligible_squares();
	const auto& pawn_eligible_squares = pawn.get_eligible_squares();
	EXPECT_EQ(std::count(pawn_eligible_squares.begin(), pawn_eligible_squares.end(), nullptr), 63);
	EXPECT_THAT(pawn_eligible_squares, IsSupersetOf({ &board[16]}));
}

TEST(PawnSquareAvailableTest, black_pawn_in_middle_of_board)
{
	BoardGame board;
	Pawn pawn{ board, board[24], std::make_unique<BlackColor>() };
	pawn.compute_eligible_squares();
	const auto& pawn_eligible_squares = pawn.get_eligible_squares();
	EXPECT_EQ(std::count(pawn_eligible_squares.begin(), pawn_eligible_squares.end(), nullptr), 63);
	EXPECT_THAT(pawn_eligible_squares, IsSupersetOf({ &board[32]}));
}


TEST(PawnSquareAvailableTest, black_pawn_at_start)
{
	BoardGame board;
	Pawn pawn{ board, board[10], std::make_unique<BlackColor>() };
	pawn.compute_eligible_squares();
	const auto& pawn_eligible_squares = pawn.get_eligible_squares();
	EXPECT_EQ(std::count(pawn_eligible_squares.begin(), pawn_eligible_squares.end(), nullptr), 62);
	EXPECT_THAT(pawn_eligible_squares, IsSupersetOf({ &board[18], &board[26]}));
}

TEST(PawnSquareAvailableTest, white_pawn_at_start)
{
	BoardGame board;
	Pawn pawn{ board, board[50], std::make_unique<WhiteColor>() };
	pawn.compute_eligible_squares();
	const auto& pawn_eligible_squares = pawn.get_eligible_squares();
	EXPECT_EQ(std::count(pawn_eligible_squares.begin(), pawn_eligible_squares.end(), nullptr), 62);
	EXPECT_THAT(pawn_eligible_squares, IsSupersetOf({ &board[42], &board[34]}));
}
