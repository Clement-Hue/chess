#include "Chess.h"

int main()
{
	Application app;
	auto& board = app.get_board();
	board.get_color(0).add_piece<King>(board[8]);
	board.get_color(1).add_piece<Rock>(board[16]);
	board.get_color(1).add_piece<Pawn>(board[1]);
	// board.set_default_pieces();
	app.init();
	return 0;
}

