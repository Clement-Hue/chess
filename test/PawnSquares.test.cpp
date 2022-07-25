#include "pch.h"
#include "game/BoardGame.h"
#include "game/Piece.h"
#include "Piece.mock.h"

TEST(PawnSquareAvailableTest, white_pawn_in_middle_of_board)
{
	BoardGame board;
	Pawn pawn{ board, board[24], std::make_unique<WhiteColor>() };
	pawn.compute_pseudo_legal_squares();
	pawn.compute_legal_squares();
	const auto& pawn_eligible_squares = pawn.get_legal_squares();
	EXPECT_EQ(std::count(pawn_eligible_squares.begin(), pawn_eligible_squares.end(), nullptr), 63);
	EXPECT_THAT(pawn_eligible_squares, IsSupersetOf({ &board[16]}));
}

TEST(PawnSquareAvailableTest, black_pawn_in_middle_of_board)
{
	BoardGame board;
	Pawn pawn{ board, board[24], std::make_unique<BlackColor>() };
	pawn.compute_pseudo_legal_squares();
	pawn.compute_legal_squares();
	const auto& pawn_eligible_squares = pawn.get_legal_squares();
	EXPECT_EQ(std::count(pawn_eligible_squares.begin(), pawn_eligible_squares.end(), nullptr), 63);
	EXPECT_THAT(pawn_eligible_squares, IsSupersetOf({ &board[32]}));
}


TEST(PawnSquareAvailableTest, black_pawn_at_start)
{
	BoardGame board;
	Pawn pawn{ board, board[10], std::make_unique<BlackColor>() };
	pawn.compute_pseudo_legal_squares();
	pawn.compute_legal_squares();
	const auto& pawn_eligible_squares = pawn.get_legal_squares();
	EXPECT_EQ(std::count(pawn_eligible_squares.begin(), pawn_eligible_squares.end(), nullptr), 62);
	EXPECT_THAT(pawn_eligible_squares, IsSupersetOf({ &board[18], &board[26]}));
}

TEST(PawnSquareAvailableTest, white_pawn_at_start)
{
	BoardGame board;
	Pawn pawn{ board, board[50], std::make_unique<WhiteColor>() };
	pawn.compute_pseudo_legal_squares();
	pawn.compute_legal_squares();
	const auto& pawn_eligible_squares = pawn.get_legal_squares();
	EXPECT_EQ(std::count(pawn_eligible_squares.begin(), pawn_eligible_squares.end(), nullptr), 62);
	EXPECT_THAT(pawn_eligible_squares, IsSupersetOf({ &board[42], &board[34]}));
}


TEST(PawnSquareAvailableTest, pawn_blocked_by_enemy)
{
	BoardGame board;
	Pawn pawn{ board, board[50], std::make_unique<WhiteColor>() };
	MockPiece piece{ board, board[42], std::make_unique<BlackColor>() };
	pawn.compute_pseudo_legal_squares();
	pawn.compute_legal_squares();
	const auto& pawn_eligible_squares = pawn.get_legal_squares();
	EXPECT_EQ(std::count(pawn_eligible_squares.begin(), pawn_eligible_squares.end(), nullptr), 64);
}


TEST(PawnSquareAvailableTest, pawn_blocked_by_friend)
{
	BoardGame board;
	Pawn pawn{ board, board[50], std::make_unique<WhiteColor>() };
	MockPiece piece{ board, board[34], std::make_unique<WhiteColor>() };
	pawn.compute_pseudo_legal_squares();
	pawn.compute_legal_squares();
	const auto& pawn_eligible_squares = pawn.get_legal_squares();
	EXPECT_EQ(std::count(pawn_eligible_squares.begin(), pawn_eligible_squares.end(), nullptr), 63);
}

TEST(PawnSquareAvailableTest, pawn_on_edge)
{
	BoardGame board;
	Pawn pawn{ board, board[1], std::make_unique<WhiteColor>() };
	pawn.compute_pseudo_legal_squares();
	const auto& pawn_eligible_squares = pawn.get_legal_squares();
	EXPECT_EQ(std::count(pawn_eligible_squares.begin(), pawn_eligible_squares.end(), nullptr), 64);
}


TEST(PawnSquareAvailableTest, takeable_black_enemy_pieces)
{
	BoardGame board;
	Pawn pawn{ board, board[50], std::make_unique<WhiteColor>() };
	MockPiece p1{ board, board[41], std::make_unique<BlackColor>() };
	MockPiece p2{ board, board[43], std::make_unique<BlackColor>() };
	pawn.compute_pseudo_legal_squares();
	const auto& pawn_eligible_squares = pawn.get_legal_squares();
	EXPECT_EQ(std::count(pawn_eligible_squares.begin(), pawn_eligible_squares.end(), nullptr), 60);
	EXPECT_THAT(pawn_eligible_squares, IsSupersetOf({ &board[41],&board[42], &board[43], &board[34]}));
}


TEST(PawnSquareAvailableTest, takeable_white_enemy_pieces)
{
	BoardGame board;
	Pawn pawn{ board, board[34], std::make_unique<BlackColor>() };
	MockPiece p1{ board, board[43], std::make_unique<WhiteColor>() };
	pawn.compute_pseudo_legal_squares();
	pawn.compute_legal_squares();
	const auto& pawn_eligible_squares = pawn.get_legal_squares();
	EXPECT_EQ(std::count(pawn_eligible_squares.begin(), pawn_eligible_squares.end(), nullptr), 62);
	EXPECT_THAT(pawn_eligible_squares, IsSupersetOf({ &board[42],&board[43]}));
}
