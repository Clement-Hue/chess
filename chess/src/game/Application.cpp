#include "Application.h"
#include <SDL2/SDL.h>
#include <stdexcept>
#include <array>
#include "EventHandler.h"
#include <memory>

std::unique_ptr<EventHandler> Application::event_handler_factory(const SDL_Event& e, bool& quit)
{
	if (e.type == SDL_QUIT)
	{
		return std::make_unique<QuitHandler>(this->board_, quit);
	}
	if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		return std::make_unique<MouseButtonHandler>(this->board_);
	}
	return nullptr;
}

void Application::app_loop()
{
	bool quit = false;
	SDL_Event e;
	while (!quit)
	{
		while (SDL_PollEvent(&e))
		{
			const auto handler = this->event_handler_factory(e, quit);
			if (handler != nullptr) (* handler)();
		}
	}
}

void Application::init()
{
	this->init_window_and_renderer();
	this->draw_board();
	this->app_loop();
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

template <uint8_t NbCases>
static std::array<SDL_Rect, NbCases> create_white_squares(const WindowSize& window_size) noexcept
{
	const int case_width = window_size.width / 8;
	const int case_height = window_size.height / 8;
	std::array<SDL_Rect, NbCases> white_squares{ { {0 ,0,case_width, case_height} } };
	for (uint8_t i = 1; i < 32; ++i)
	{
		white_squares[i].x = white_squares[i - 1].x + 2 * case_width;
		white_squares[i].y = white_squares[i - 1].y;

		if (i % 4 == 0) // line break
		{
			white_squares[i].x = (i % 8 == 0) ? 0 : case_width;
			white_squares[i].y = white_squares[i - 1].y + case_height;
		}
		white_squares[i].w = case_width;
		white_squares[i].h = case_height;
	}
	return white_squares;
}


void Application::draw_board() const noexcept
{
	constexpr uint8_t nb_rect = 32;
	SDL_SetRenderDrawColor(this->renderer_, this->primary_color_.r, this->primary_color_.g,
		this->primary_color_.b, this->primary_color_.a);
	SDL_RenderClear(this->renderer_);
	SDL_SetRenderDrawColor(this->renderer_, this->secondary_color_.r, this->secondary_color_.g, 
		this->secondary_color_.b, this->secondary_color_.a);
	const auto white_squares = create_white_squares<nb_rect>(this->window_size_);
	SDL_RenderFillRects(this->renderer_, white_squares.data(), nb_rect);
	SDL_RenderPresent(this->renderer_);
}
