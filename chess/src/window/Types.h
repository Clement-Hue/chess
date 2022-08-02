#pragma once

struct WindowSize
{
	const int width, height;
};

struct CaseColor
{
	int r, g, b, a;
};


struct Asset
{
	Piece& piece;
	SDL_Texture* texture;
};
