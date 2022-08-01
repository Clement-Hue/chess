#include "Chess.h"

int main()
{
	Application app;
	auto& board = app.get_board();
	board.get_color(0).add_piece<Pawn>(board[8]);
	app.init();
	return 0;
}

