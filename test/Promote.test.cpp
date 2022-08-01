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
