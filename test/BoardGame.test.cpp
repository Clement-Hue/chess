#include "pch.h"
#include "game/BoardGame.h"
#include "Piece.mock.h"

TEST(BoardGameTest, should_alternate_turn)
{
	BoardGame board;
	auto& w_piece = board.get_color(0).add_piece<Pawn>(board[48]);
	auto& b_piece = board.get_color(1).add_piece<Pawn>(board[8]);
	board.init_game();
	EXPECT_TRUE(board.get_turn() == WhiteColor(board));
	w_piece.move(board[40]);
	EXPECT_TRUE(board.get_turn() == BlackColor(board));
	b_piece.move(board[16]);
	EXPECT_TRUE(board.get_turn() == WhiteColor(board));
}

TEST(BoardGameTest, should_simulate_a_game)
{
	BoardGame board;
	board.set_default_pieces();
	board.init_game();
	auto& pawn_b = board.get_color(1).get_piece(12);
	auto& pawn_w = board.get_color(0).get_piece(11);
	EXPECT_TRUE(pawn_b.get_legal_move(21)) << "black pseudo legal square invalid";
	EXPECT_FALSE(pawn_w.get_legal_move(44)) << "white legal square invalid";
	pawn_w.move(board[35]);
	EXPECT_EQ(*pawn_w.get_square(), board[35]) << "white hasn't moved";
	EXPECT_FALSE(pawn_b.get_legal_move(21)) << "black legal square hasn't been computed";
	pawn_b.move( board[28]);
	EXPECT_EQ(*pawn_b.get_square(), board[28]) << "black hasn't moved";
	pawn_w.move(board[28]);
	EXPECT_EQ(*pawn_w.get_square(), board[28]) << "white hasn't taken black";
	EXPECT_EQ(pawn_b.get_square(), nullptr) << "black pawn still on the game";
}

TEST(BoardGameTest, should_clear_legal_square_between_move)
{
	BoardGame board;
	auto& pawn_w = board.get_color(0).add_piece<Pawn>(board[48]);
	board.init_game();
	EXPECT_TRUE(pawn_w.move(board[40]));
	EXPECT_FALSE(pawn_w.get_legal_move(40));
}
