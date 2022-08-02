#include "pch.h"
#include "Matchers.h"
#include "game/BoardGame.h"


TEST(InPassingTest, white_pawn_is_takeable)
{
	BoardGame board;
	auto& pawn_w = board.get_color(0).add_piece<Pawn>(board[50]);
	auto& pawn_b = board.get_color(1).add_piece<Pawn>(board[33]);
	board.init_game();
	EXPECT_TRUE(pawn_w.move(board[34]));
	EXPECT_TRUE(pawn_w.has_double_moved());
	EXPECT_TRUE(pawn_w.has_moved());
	has_squares(pawn_b.get_legal_moves(), { 41, 42 });
	pawn_b.move(board[42]);
	EXPECT_FALSE(pawn_w.has_double_moved());
}

TEST(InPassingTest, blacke_pawn_is_takeable)
{
	BoardGame board;
	auto& pawn_b = board.get_color(1).add_piece<Pawn>(board[10]);
	auto& pawn_w = board.get_color(0).add_piece<Pawn>(board[25]);
	board.init_game(1);
	EXPECT_TRUE(pawn_b.move(board[26]));
	EXPECT_TRUE(pawn_b.has_double_moved());
	EXPECT_TRUE(pawn_b.has_moved());
	has_squares(pawn_w.get_legal_moves(), { 17, 18  });
	pawn_w.move(board[18]);
	EXPECT_FALSE(pawn_b.has_double_moved());
}


TEST(InPassingTest, taking_piece_in_passing)
{
	BoardGame board;
	auto& pawn_w = board.get_color(0).add_piece<Pawn>(board[50]);
	auto& pawn_b = board.get_color(1).add_piece<Pawn>(board[33]);
	board.init_game();
	pawn_w.move(board[34]);
	pawn_b.move(board[42]);
	EXPECT_EQ(pawn_w.get_square(), nullptr) << "white pawn still on board";
	EXPECT_EQ(board[34].get_piece(), nullptr) << "square 34 not empty";
	EXPECT_EQ(board[42].get_piece(), &pawn_b) << "black pawn hasn't moved";
	EXPECT_TRUE(pawn_b.has_moved());
}
