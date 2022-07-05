#include "BoardGame.h"
#include <SDL2/SDL.h>
#include <stdexcept>

static constexpr uint32_t WIDTH = 600;
static constexpr uint32_t HEIGHT = 600;

void loader::BoardGame::create_window()
{
	this->init_window_and_renderer();
	this->draw_board();
	SDL_Delay(3000);
}

loader::BoardGame::~BoardGame()
{
	SDL_DestroyWindow(this->window_);
	SDL_DestroyRenderer(this->renderer_);
	SDL_Quit();
}

void loader::BoardGame::init_window_and_renderer()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	this->window_ = SDL_CreateWindow("Chess", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE);
	this->renderer_ = SDL_CreateRenderer(this->window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (this->renderer_ == nullptr)
	{
		throw std::runtime_error("Unable to create the renderer");
	}
	if (this->window_ == nullptr)
	{
		throw std::runtime_error("Unable to create the window");
	}
}

static void create_rectangles(SDL_Rect white_cases[])
{
	constexpr int CASE_WIDTH = WIDTH / 8;
	constexpr int CASE_HEIGHT = HEIGHT / 8;
	white_cases[0] = {0,0,CASE_WIDTH, CASE_HEIGHT};
	for (uint8_t i = 1; i != 32; i++)
	{
		white_cases[i].x = white_cases[i - 1].x + 2 * CASE_WIDTH;
		white_cases[i].y = white_cases[i - 1].y;

		if (i % 4 == 0) // line break
		{
			white_cases[i].x = (i % 8 == 0) ? 0 : CASE_WIDTH;
			white_cases[i].y = white_cases[i - 1].y + CASE_HEIGHT;
		}
		white_cases[i].w = CASE_WIDTH;
		white_cases[i].h = CASE_HEIGHT;
	}
}


void loader::BoardGame::draw_board() const noexcept
{
	constexpr uint8_t NB_CASES = 32;
	SDL_SetRenderDrawColor(this->renderer_, this->primary_color_.r, this->primary_color_.g,
		this->primary_color_.b, this->primary_color_.a);
	SDL_RenderClear(this->renderer_);
	SDL_SetRenderDrawColor(this->renderer_, this->secondary_color_.r, this->secondary_color_.g, 
		this->secondary_color_.b, this->secondary_color_.a);
	SDL_Rect white_cases[NB_CASES];
	create_rectangles(white_cases);
	SDL_RenderFillRects(this->renderer_, white_cases, NB_CASES);
	SDL_RenderPresent(this->renderer_);
}
