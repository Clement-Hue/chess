#include "pch.h"
#include "Matchers.h"
#include "game/BoardGame.h"

TEST(KingIllegalMovesTest, squares_attacked_by_queen)
{
	BoardGame board;
	board.get_color(1).add_piece<Queen>(board[7]);
	const auto& king = board.get_color(0).add_piece<King>(board[11]);
	board.get_color(0).add_piece<Rock>(board[21]);
	board.init_game();
	const auto& king_eligible_squares = king.get_legal_moves();
	has_squares(king_eligible_squares, { 10,12,18,19,20 });
}

TEST(KingIllegalMovesTest, squares_attacked_by_bishop)
{
	BoardGame board;
	board.get_color(1).add_piece<Bishop>(board[29]);
	const auto& king = board.get_color(0).add_piece<King>(board[11]);
	board.init_game();
	const auto& king_eligible_squares = king.get_legal_moves();
	has_squares(king_eligible_squares, { 3,4,10,12,18,19 });
}


TEST(KingIllegalMovesTest, squares_attacked_by_pawn)
{
	BoardGame board;
	board.get_color(1).add_piece<Pawn>(board[3]);
	const auto& king = board.get_color(0).add_piece<King>(board[19]);
	board.init_game();
	const auto& king_eligible_squares = king.get_legal_moves();
	has_squares(king_eligible_squares, { 11,18,20,26,27,28 });
}

TEST(KingIllegalMovesTest, squares_attacked_by_rock)
{
	BoardGame board;
	board.get_color(1).add_piece<Rock>(board[27]);
	const auto& king = board.get_color(0).add_piece<King>(board[11]);
	board.init_game();
	const auto& king_eligible_squares = king.get_legal_moves();
	has_squares(king_eligible_squares, { 2,4,10,12,18,20 });
}


TEST(KingIllegalMovesTest, squares_attacked_by_knight)
{
	BoardGame board;
	board.get_color(1).add_piece<Knight>(board[29]);
	const auto& king = board.get_color(0).add_piece<King>(board[11]);
	board.init_game();
	const auto& king_eligible_squares = king.get_legal_moves();
	has_squares(king_eligible_squares, { 2,3,4,10,18,20 });
}

TEST(KingIllegalMovesTest, squares_attacked_by_king)
{
	BoardGame board;
	board.get_color(1).add_piece<King>(board[13]);
	const auto& king = board.get_color(0).add_piece<King>(board[11]);
	board.init_game();
	const auto& king_eligible_squares = king.get_legal_moves();
	has_squares(king_eligible_squares, { 2,3,10,18,19 });
}
