#include "Chess.h"

int main()
{
	Application app;
	auto& board = app.get_board();
	board.get_color(1).add_piece<Rock>(board[35]);
	board.get_color(0).add_piece<King>(board[11]);
	board.get_color(0).add_piece<Bishop>(board[20]);
	// board.set_default_pieces();
	app.init();
	return 0;
}

