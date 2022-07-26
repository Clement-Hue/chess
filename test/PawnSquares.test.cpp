#include "pch.h"
#include "game/BoardGame.h"
#include "game/Piece.h"
#include "Piece.mock.h"

TEST(PawnSquareAvailableTest, white_pawn_in_middle_of_board)
{
	BoardGame board;
	auto& pawn = board.get_color(0).create_piece<Pawn>(&board[24]);
	pawn.compute_pseudo_legal_squares();
	pawn.compute_legal_squares();
	const auto& pawn_eligible_squares = pawn.get_legal_squares();
	EXPECT_EQ(std::count(pawn_eligible_squares.begin(), pawn_eligible_squares.end(), nullptr), 63);
	EXPECT_THAT(pawn_eligible_squares, IsSupersetOf({ &board[16]}));
}

TEST(PawnSquareAvailableTest, black_pawn_in_middle_of_board)
{
	BoardGame board;
	auto& pawn = board.get_color(1).create_piece<Pawn>(&board[24]);
	pawn.compute_pseudo_legal_squares();
	pawn.compute_legal_squares();
	const auto& pawn_eligible_squares = pawn.get_legal_squares();
	EXPECT_EQ(std::count(pawn_eligible_squares.begin(), pawn_eligible_squares.end(), nullptr), 63);
	EXPECT_THAT(pawn_eligible_squares, IsSupersetOf({ &board[32]}));
}


TEST(PawnSquareAvailableTest, black_pawn_at_start)
{
	BoardGame board;
	auto& pawn = board.get_color(1).create_piece<Pawn>(&board[10]);
	pawn.compute_pseudo_legal_squares();
	pawn.compute_legal_squares();
	const auto& pawn_eligible_squares = pawn.get_legal_squares();
	EXPECT_EQ(std::count(pawn_eligible_squares.begin(), pawn_eligible_squares.end(), nullptr), 62);
	EXPECT_THAT(pawn_eligible_squares, IsSupersetOf({ &board[18], &board[26]}));
}

TEST(PawnSquareAvailableTest, white_pawn_at_start)
{
	BoardGame board;
	auto& pawn = board.get_color(0).create_piece<Pawn>(&board[50]);
	pawn.compute_pseudo_legal_squares();
	pawn.compute_legal_squares();
	const auto& pawn_eligible_squares = pawn.get_legal_squares();
	EXPECT_EQ(std::count(pawn_eligible_squares.begin(), pawn_eligible_squares.end(), nullptr), 62);
	EXPECT_THAT(pawn_eligible_squares, IsSupersetOf({ &board[42], &board[34]}));
}


TEST(PawnSquareAvailableTest, pawn_blocked_by_enemy)
{
	BoardGame board;
	auto& pawn = board.get_color(0).create_piece<Pawn>(&board[50]);
	board.get_color(1).create_piece<MockPiece>(&board[42]);
	pawn.compute_pseudo_legal_squares();
	pawn.compute_legal_squares();
	const auto& pawn_eligible_squares = pawn.get_legal_squares();
	EXPECT_EQ(std::count(pawn_eligible_squares.begin(), pawn_eligible_squares.end(), nullptr), 64);
}


TEST(PawnSquareAvailableTest, pawn_blocked_by_friend)
{
	BoardGame board;
	auto& pawn = board.get_color(0).create_piece<Pawn>(&board[50]);
	board.get_color(0).create_piece<MockPiece>(&board[34]);
	pawn.compute_pseudo_legal_squares();
	pawn.compute_legal_squares();
	const auto& pawn_eligible_squares = pawn.get_legal_squares();
	EXPECT_EQ(std::count(pawn_eligible_squares.begin(), pawn_eligible_squares.end(), nullptr), 63);
}

TEST(PawnSquareAvailableTest, pawn_on_edge)
{
	BoardGame board;
	auto& pawn = board.get_color(0).create_piece<Pawn>(&board[1]);
	pawn.compute_pseudo_legal_squares();
	const auto& pawn_eligible_squares = pawn.get_legal_squares();
	EXPECT_EQ(std::count(pawn_eligible_squares.begin(), pawn_eligible_squares.end(), nullptr), 64);
}


TEST(PawnSquareAvailableTest, takeable_black_enemy_pieces)
{
	BoardGame board;
	auto& pawn = board.get_color(0).create_piece<Pawn>(&board[50]);
	board.get_color(1).create_piece<MockPiece>(&board[41]);
	board.get_color(1).create_piece<MockPiece>(&board[43]);
	pawn.compute_pseudo_legal_squares();
	const auto& pawn_eligible_squares = pawn.get_legal_squares();
	EXPECT_EQ(std::count(pawn_eligible_squares.begin(), pawn_eligible_squares.end(), nullptr), 60);
	EXPECT_THAT(pawn_eligible_squares, IsSupersetOf({ &board[41],&board[42], &board[43], &board[34]}));
}


TEST(PawnSquareAvailableTest, takeable_white_enemy_pieces)
{
	BoardGame board;
	auto& pawn = board.get_color(1).create_piece<Pawn>(&board[34]);
	board.get_color(0).create_piece<MockPiece>(&board[43]);
	pawn.compute_pseudo_legal_squares();
	pawn.compute_legal_squares();
	const auto& pawn_eligible_squares = pawn.get_legal_squares();
	EXPECT_EQ(std::count(pawn_eligible_squares.begin(), pawn_eligible_squares.end(), nullptr), 62);
	EXPECT_THAT(pawn_eligible_squares, IsSupersetOf({ &board[42],&board[43]}));
}
