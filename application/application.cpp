#include "Chess.h"

int main()
{
	Application app;
	app.get_board().get_color(0).add_piece(
		std::make_unique<Rock>(&app.get_board()[25])
	);
	app.init();
	return 0;
}

