#include "Application.h"
#include <SDL2/SDL.h>
#include <stdexcept>


void Application::init()
{
	this->init_window_and_renderer();
	this->draw_board();
	SDL_Delay(3000);
}


Application::~Application()
{
	SDL_DestroyWindow(this->window_);
	SDL_DestroyRenderer(this->renderer_);
	SDL_Quit();
}

void Application::init_window_and_renderer()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	this->window_ = SDL_CreateWindow("Chess", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, this->window_size_.width, this->window_size_.height,
		SDL_WINDOW_RESIZABLE);
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

static void create_squares(SDL_Rect white_cases[], const WindowSize& window_size)
{
	const int case_width = window_size.width / 8;
	const int case_height = window_size.height / 8;
	white_cases[0] = {0,0,case_width, case_height};
	for (uint8_t i = 1; i < 32; ++i)
	{
		white_cases[i].x = white_cases[i - 1].x + 2 * case_width;
		white_cases[i].y = white_cases[i - 1].y;

		if (i % 4 == 0) // line break
		{
			white_cases[i].x = (i % 8 == 0) ? 0 : case_width;
			white_cases[i].y = white_cases[i - 1].y + case_height;
		}
		white_cases[i].w = case_width;
		white_cases[i].h = case_height;
	}
}


void Application::draw_board() const noexcept
{
	constexpr uint8_t nb_rect = 32;
	SDL_SetRenderDrawColor(this->renderer_, this->primary_color_.r, this->primary_color_.g,
		this->primary_color_.b, this->primary_color_.a);
	SDL_RenderClear(this->renderer_);
	SDL_SetRenderDrawColor(this->renderer_, this->secondary_color_.r, this->secondary_color_.g, 
		this->secondary_color_.b, this->secondary_color_.a);
	SDL_Rect white_cases[nb_rect];
	create_squares(white_cases, this->window_size_);
	SDL_RenderFillRects(this->renderer_, white_cases, nb_rect);
	SDL_RenderPresent(this->renderer_);
}
