#include "Chess.h"

int main()
{
	Application app;
	const auto& board = app.get_board();
	//board.get_color(0).add_piece<Pawn>(board[8]);
	board.set_default_pieces();
	app.init();
	return 0;
}

