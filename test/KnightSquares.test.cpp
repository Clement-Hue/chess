#include "pch.h"
#include "Matchers.h"
#include "game/BoardGame.h"
#include "game/Piece.h"

TEST(KnightSquareAvailableTest, all_squares_free)
{
	BoardGame board;
	const auto& knight = board.get_color(0).add_piece<Knight>(board[35]);
	board.init_game(0);
	const auto& bishop_eligible_squares = knight.get_legal_moves();
	has_squares(bishop_eligible_squares, { 18,20,25,29,41,45,50,52 });
}


TEST(KnightSquareAvailableTest, squares_taken_by_friends)
{
	BoardGame board;
	const auto& knight = board.get_color(0).add_piece<Knight>(board[35]);
	board.get_color(0).add_piece<Pawn>(board[18]);
	board.get_color(0).add_piece<Pawn>(board[50]);
	board.init_game(0);
	const auto& bishop_eligible_squares = knight.get_legal_moves();
	has_squares(bishop_eligible_squares, { 20,25,29,41,45,52 });
}

