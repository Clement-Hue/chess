#include "pch.h"
#include "Matchers.h"
#include "game/BoardGame.h"

TEST(PromoteMoveTest, promote_white_pawn_on_last_rank)
{
	BoardGame board;
	auto& pawn = board.get_color(0).add_piece<Pawn>(board[8]);
	EXPECT_EQ(board.get_color(0).get_pieces().size(), 1);
	board.init_game();
	has_squares(pawn.get_legal_moves(), { 0 });
	pawn.move(board[0]);
	const auto& piece = board[0].get_piece();
	EXPECT_EQ(board[8].get_piece(), nullptr);
	EXPECT_EQ(piece->get_square(), &board[0]);
	EXPECT_TRUE(dynamic_cast<Queen*>(piece));
	EXPECT_EQ(board.get_color(0).get_pieces().size(), 1);
	EXPECT_TRUE(dynamic_cast<Queen*>(&board.get_color(0).get_piece(0)));
}


TEST(PromoteMoveTest, promote_black_pawn_on_last_rank)
{
	BoardGame board;
	auto& pawn = board.get_color(1).add_piece<Pawn>(board[50]);
	EXPECT_EQ(board.get_color(1).get_pieces().size(), 1);
	board.init_game(1);
	has_squares(pawn.get_legal_moves(), { 58 });
	pawn.move(board[58]);
	const auto& piece = board[58].get_piece();
	EXPECT_EQ(board[50].get_piece(), nullptr);
	EXPECT_EQ(piece->get_square(), &board[58]);
	EXPECT_TRUE(dynamic_cast<Queen*>(piece));
	EXPECT_EQ(board.get_color(1).get_pieces().size(), 1);
	EXPECT_TRUE(dynamic_cast<Queen*>(&board.get_color(1).get_piece(0)));
}


TEST(PromoteMoveTest, promote_when_capturing)
{
	BoardGame board;
	auto& pawn = board.get_color(0).add_piece<Pawn>(board[8]);
	const auto& rock = board.get_color(1).add_piece<Rock>(board[1]);
	board.init_game();
	has_squares(pawn.get_legal_moves(), { 0, 1 });
	pawn.move(board[1]);
	const auto& piece = board[1].get_piece();
	EXPECT_EQ(board[8].get_piece(), nullptr);
	EXPECT_EQ(piece->get_square(), &board[1]);
	EXPECT_TRUE(dynamic_cast<Queen*>(piece));
	EXPECT_EQ(rock.get_square(), nullptr);
}

