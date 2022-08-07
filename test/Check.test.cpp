#include "pch.h"
#include "Matchers.h"
#include "game/BoardGame.h"
#include "game/Piece.h"

TEST(CheckTest, rock_check)
{
	BoardGame board;
	board.get_color(1).add_piece<Rock>(board[35]);
	const auto& bishop = board.get_color(0).add_piece<Bishop>(board[20]);
	const auto& rock = board.get_color(0).add_piece<Rock>(board[16]);
	const auto& king = board.get_color(0).add_piece<King>(board[11]);
	board.init_game();
	has_squares(bishop.get_legal_moves(), { 27 });
	has_squares(rock.get_legal_moves(), { 19 });
	has_squares(king.get_legal_moves(), { 2,4,10,12,18 });
}

TEST(CheckTest, queen_check)
{
	BoardGame board;
	board.get_color(1).add_piece<Queen>(board[38]);
	const auto& rock = board.get_color(0).add_piece<Rock>(board[25]);
	const auto& king = board.get_color(0).add_piece<King>(board[11]);
	board.init_game();
	has_squares(rock.get_legal_moves(), { 29 });
	has_squares(king.get_legal_moves(), { 3 ,4 ,10, 12, 18, 19 });
}

TEST(CheckTest, bishop_check)
{
	BoardGame board;
	board.get_color(1).add_piece<Bishop>(board[6]);
	const auto& bishop = board.get_color(0).add_piece<Bishop>(board[15]);
	const auto& king = board.get_color(0).add_piece<King>(board[20]);
	board.init_game();
	has_squares(bishop.get_legal_moves(), { 6 });
	has_squares(king.get_legal_moves(), {  11, 12, 19, 21,28 ,29 });
}

TEST(CheckTest, knight_check)
{
	BoardGame board;
	board.get_color(1).add_piece<Knight>(board[37]);
	const auto& king = board.get_color(0).add_piece<King>(board[20]);
	const auto& rock = board.get_color(0).add_piece<Rock>(board[35]);
	board.init_game();
	has_squares(rock.get_legal_moves(), { 37 });
	has_squares(king.get_legal_moves(), {  11, 12, 13, 19, 21,28 ,29 });
}
TEST(CheckTest, pawn_check)
{
	BoardGame board;
	board.get_color(1).add_piece<Pawn>(board[13]);
	const auto& king = board.get_color(0).add_piece<King>(board[20]);
	const auto& rock = board.get_color(0).add_piece<Rock>(board[10]);
	board.init_game();
	has_squares(rock.get_legal_moves(), { 13 });
	has_squares(king.get_legal_moves(), {  11, 12, 13, 19, 21,27,28 ,29 });
}

