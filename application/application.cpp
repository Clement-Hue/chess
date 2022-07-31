#include "Chess.h"

int main()
{
	Application app;
	auto& board = app.get_board();
	board.get_color(0).add_piece<King>(board[60]);
	board.get_color(1).add_piece<Rock>(board[4]);
	board.get_color(0).add_piece<Rock>(board[56]);
	app.init();
	return 0;
}

