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
	has_squares(king.get_legal_moves(), { 2,10, 12,4, 18 });
}