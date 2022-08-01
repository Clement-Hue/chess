#include "pch.h"
#include "Matchers.h"
#include "game/BoardGame.h"
#include "game/Piece.h"

TEST(PawnSquareAvailableTest, white_pawn_in_middle_of_board)
{
	BoardGame board;
	auto& pawn = board.get_color(0).add_piece<Pawn>(board[24]);
	pawn.compute_pseudo_legal_moves();
	pawn.compute_legal_moves();
	const auto& pawn_eligible_squares = pawn.get_legal_moves();
	has_squares(pawn_eligible_squares, { 16 });
}

TEST(PawnSquareAvailableTest, black_pawn_in_middle_of_board)
{
	BoardGame board;
	auto& pawn = board.get_color(1).add_piece<Pawn>(board[24]);
	pawn.compute_pseudo_legal_moves();
	pawn.compute_legal_moves();
	const auto& pawn_eligible_squares = pawn.get_legal_moves();
	has_squares(pawn_eligible_squares, { 32 });
}


TEST(PawnSquareAvailableTest, black_pawn_at_start)
{
	BoardGame board;
	auto& pawn = board.get_color(1).add_piece<Pawn>(board[10]);
	pawn.compute_pseudo_legal_moves();
	pawn.compute_legal_moves();
	const auto& pawn_eligible_squares = pawn.get_legal_moves();
	has_squares(pawn_eligible_squares, { 18,26 });
}

TEST(PawnSquareAvailableTest, white_pawn_at_start)
{
	BoardGame board;
	auto& pawn = board.get_color(0).add_piece<Pawn>(board[50]);
	pawn.compute_pseudo_legal_moves();
	pawn.compute_legal_moves();
	const auto& pawn_eligible_squares = pawn.get_legal_moves();
	has_squares(pawn_eligible_squares, { 34,42 });
}


TEST(PawnSquareAvailableTest, pawn_blocked_by_enemy)
{
	BoardGame board;
	auto& pawn = board.get_color(0).add_piece<Pawn>(board[50]);
	board.get_color(1).add_piece<Pawn>(board[42]);
	pawn.compute_pseudo_legal_moves();
	pawn.compute_legal_moves();
	const auto& pawn_eligible_squares = pawn.get_legal_moves();
	EXPECT_EQ(std::count(pawn_eligible_squares.begin(), pawn_eligible_squares.end(), nullptr), 64);
}


TEST(PawnSquareAvailableTest, pawn_blocked_by_friend)
{
	BoardGame board;
	auto& pawn = board.get_color(0).add_piece<Pawn>(board[50]);
	board.get_color(0).add_piece<Pawn>(board[34]);
	pawn.compute_pseudo_legal_moves();
	pawn.compute_legal_moves();
	const auto& pawn_eligible_squares = pawn.get_legal_moves();
	has_squares(pawn_eligible_squares, { 42 });
}

TEST(PawnSquareAvailableTest, pawn_on_edge)
{
	BoardGame board;
	auto& pawn = board.get_color(0).add_piece<Pawn>(board[1]);
	pawn.compute_pseudo_legal_moves();
	const auto& pawn_eligible_squares = pawn.get_legal_moves();
	EXPECT_EQ(std::count(pawn_eligible_squares.begin(), pawn_eligible_squares.end(), nullptr), 64);
}


TEST(PawnSquareAvailableTest, takeable_black_enemy_pieces)
{
	BoardGame board;
	auto& pawn = board.get_color(0).add_piece<Pawn>(board[50]);
	board.get_color(1).add_piece<Pawn>(board[41]);
	board.get_color(1).add_piece<Pawn>(board[43]);
	pawn.compute_pseudo_legal_moves();
	pawn.compute_legal_moves();
	const auto& pawn_eligible_squares = pawn.get_legal_moves();
	has_squares(pawn_eligible_squares, { 34, 41,42,43 });
}


TEST(PawnSquareAvailableTest, takeable_white_enemy_pieces)
{
	BoardGame board;
	auto& pawn = board.get_color(1).add_piece<Pawn>(board[34]);
	board.get_color(0).add_piece<Pawn>(board[43]);
	pawn.compute_pseudo_legal_moves();
	pawn.compute_legal_moves();
	const auto& pawn_eligible_squares = pawn.get_legal_moves();
	has_squares(pawn_eligible_squares, { 42, 43 });
}
