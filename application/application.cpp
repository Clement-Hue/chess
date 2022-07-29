#include "Chess.h"

int main()
{
	Application app;
	const auto& board = app.get_board();
	board.set_default_pieces();
	app.init();
	return 0;
}

