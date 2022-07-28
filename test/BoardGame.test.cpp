#include "pch.h"
#include "game/BoardGame.h"
#include "Piece.mock.h"

TEST(BoardGameTest, should_alternate_turn)
{
	BoardGame board;
	auto& w_piece = board.get_color(0).create_piece<Pawn>(&board[48]);
	auto& b_piece = board.get_color(1).create_piece<Pawn>(&board[8]);
	EXPECT_TRUE(board.get_turn() == WhiteColor(board));
	w_piece.compute_pseudo_legal_squares();
	w_piece.compute_legal_squares();
	w_piece.move(board[40]);
	EXPECT_TRUE(board.get_turn() == BlackColor(board));
	b_piece.compute_pseudo_legal_squares();
	b_piece.compute_legal_squares();
	b_piece.move(board[16]);
	EXPECT_TRUE(board.get_turn() == WhiteColor(board));
}

TEST(BoardGameTest, should_simulate_a_game)
{
	BoardGame board;
	board.init_game();
	auto& pawn_b = board.get_color(1).get_piece(0);
	auto& pawn_w = board.get_color(0).get_piece(0);
	EXPECT_TRUE(pawn_b.get_legal_square(17));
	pawn_w.move(board[40]);
	EXPECT_EQ(*pawn_w.get_square(), board[40]);
	EXPECT_FALSE(pawn_b.get_legal_square(17));
	pawn_b.move( board[16]);
	EXPECT_EQ(*pawn_b.get_square(), board[16]);
}
