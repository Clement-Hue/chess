#include "pch.h"
#include "Matchers.h"
#include "game/BoardGame.h"
#include "game/Piece.h"

TEST(KingSquareAvailableTest, all_squares_free)
{
	BoardGame board;
	const auto& knight = board.get_color(0).add_piece<King>(board[11]);
	board.init_game();
	const auto& king_eligible_squares = knight.get_legal_moves();
	has_squares(king_eligible_squares, { 2,3,4,10,12,18,19,20 });
}


TEST(KingSquareAvailableTest, enemy_piece_protected)
{
	BoardGame board;
	board.get_color(1).add_piece<Pawn>(board[20]);
	board.get_color(1).add_piece<Rock>(board[36]);
	const auto& knight = board.get_color(0).add_piece<King>(board[11]);
	board.init_game();
	const auto& king_eligible_squares = knight.get_legal_moves();
	has_squares(king_eligible_squares, { 2,3,4,10,12,18,19 });
}

TEST(KingSquareAvailableTest, positionned_on_edge)
{
	BoardGame board;
	const auto& king = board.get_color(0).add_piece<King>(board[63]);
	board.init_game();
	const auto& king_eligible_squares = king.get_legal_moves();
	has_squares(king_eligible_squares,{ 54,55,62 });
}


TEST(KingSquareAvailableTest, squares_taken)
{
	BoardGame board;
	board.get_color(0).add_piece<Pawn>(board[18]);
	board.get_color(0).add_piece<Pawn>(board[3]);
	board.get_color(1).add_piece<Pawn>(board[2]);
	const auto& king = board.get_color(0).add_piece<King>(board[11]);
	board.init_game();
	const auto& king_eligible_squares = king.get_legal_moves();
	has_squares(king_eligible_squares, { 2,4,10,12,19,20 });
}


