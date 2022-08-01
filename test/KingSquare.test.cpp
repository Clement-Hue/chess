#include "pch.h"
#include "Matchers.h"
#include "game/BoardGame.h"
#include "game/Piece.h"

TEST(KingSquareAvailableTest, all_squares_free)
{
	BoardGame board;
	auto& knight = board.get_color(0).add_piece<King>(board[11]);
	knight.compute_pseudo_legal_moves();
	const auto& king_eligible_squares = knight.get_legal_moves();
	has_squares(king_eligible_squares, { 2,3,4,10,12,18,19,20 });
}

TEST(KingSquareAvailableTest, positionned_on_edge)
{
	BoardGame board;
	auto& king = board.get_color(0).add_piece<King>(board[63]);
	king.compute_pseudo_legal_moves();
	const auto& king_eligible_squares = king.get_legal_moves();
	has_squares(king_eligible_squares,{ 54,55,62 });
}


TEST(KingSquareAvailableTest, squares_taken)
{
	BoardGame board;
	board.get_color(0).add_piece<Pawn>(board[18]);
	board.get_color(0).add_piece<Pawn>(board[3]);
	board.get_color(1).add_piece<Pawn>(board[2]);
	auto& king = board.get_color(0).add_piece<King>(board[11]);
	king.compute_pseudo_legal_moves();
	const auto& king_eligible_squares = king.get_legal_moves();
	has_squares(king_eligible_squares, { 2,4,10,12,19,20 });
}


TEST(KingSquareAvailableTest, squares_attacked)
{
	BoardGame board;
	board.get_color(1).add_piece<Rock>(board[7]);
	const auto& king = board.get_color(0).add_piece<King>(board[11]);
	board.get_color(0).add_piece<Rock>(board[21]);
	board.init_game();
	const auto& king_eligible_squares = king.get_legal_moves();
	has_squares(king_eligible_squares, { 10,12,18,19,20 });
}


TEST(KingSquareAvailableTest, pawn_attack_squares)
{
	BoardGame board;
	board.get_color(1).add_piece<Pawn>(board[3]);
	const auto& king = board.get_color(0).add_piece<King>(board[19]);
	board.init_game();
	const auto& king_eligible_squares = king.get_legal_moves();
	has_squares(king_eligible_squares, { 11,18,20,26,27,28 });
}

