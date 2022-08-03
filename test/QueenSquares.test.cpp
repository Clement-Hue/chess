#include "pch.h"
#include "Matchers.h"
#include "game/BoardGame.h"
#include "game/Piece.h"


TEST(QueenSquareAvailableTest, all_squares_free)
{
	BoardGame board;
	const auto& queen = board.get_color(0).add_piece<Queen>(board[11]);
	board.init_game();
	const auto& queen_eligible_squares = queen.get_legal_moves();
	has_squares(queen_eligible_squares, { 2,3,4,8,9,10,12,13,14,15,18,19,20,
		25,27,29,32,35,38,43,47,51,59 });
}


TEST(QueenSquareAvailableTest, squares_taken)
{
	BoardGame board;
	board.get_color(0).add_piece<Pawn>(board[25]);
	board.get_color(0).add_piece<Pawn>(board[38]);
	board.get_color(1).add_piece<Pawn>(board[2]);
	board.get_color(1).add_piece<Pawn>(board[27]);
	const auto& queen = board.get_color(0).add_piece<Queen>(board[11]);
	board.init_game();
	const auto& queen_eligible_squares = queen.get_legal_moves();
	has_squares(queen_eligible_squares, { 2,3,4,8,9,10,12,13,14,15,18,19,20,27,29 });
}

