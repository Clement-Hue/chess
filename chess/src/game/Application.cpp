#include <SDL2/SDL.h>
#include "SDL2/SDL_image.h"
#include "Application.h"
#include <stdexcept>
#include <array>
#include <memory>
#include "EventHandler.h"

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
			if (const auto handler = this->event_handler_factory(e, quit))
			{
				(*handler)();
			}
		}
	}
}


void Application::init()
{
	this->init_window_and_renderer();
	this->draw_board();
	this->load_assets();
	this->app_loop();
}


Application::~Application()
{
	for (const auto sprite : this->sprites_)
	{
		SDL_DestroyTexture(sprite);
	}
	SDL_DestroyRenderer(this->renderer_);
	SDL_DestroyWindow(this->window_);
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

template <uint8_t NbRect>
static std::array<SDL_Rect, NbRect> create_white_squares(const int case_width, const int case_height) noexcept
{
	std::array<SDL_Rect, NbRect> white_squares{ { {0 ,0,case_width, case_height} } };
	for (uint8_t i = 1; i < NbRect; ++i)
	{
		white_squares[i].x = white_squares[i - 1].x + 2 * case_width;
		white_squares[i].y = white_squares[i - 1].y;

		if (i % 4 == 0) // line break
		{
			white_squares[i].x = (i % NB_COLUMNS == 0) ? 0 : case_width;
			white_squares[i].y = white_squares[i - 1].y + case_height;
		}
		white_squares[i].w = case_width;
		white_squares[i].h = case_height;
	}
	return white_squares;
}


void Application::draw_board() const noexcept
{
	constexpr uint8_t nb_rect = NB_SQUARES / 2;
	SDL_SetRenderDrawColor(this->renderer_, this->primary_color_.r, this->primary_color_.g,
		this->primary_color_.b, this->primary_color_.a);
	SDL_RenderClear(this->renderer_);
	SDL_SetRenderDrawColor(this->renderer_, this->secondary_color_.r, this->secondary_color_.g, 
		this->secondary_color_.b, this->secondary_color_.a);
	const auto [case_width, case_height] = this->get_case_dimensions();
	const auto white_squares = create_white_squares<nb_rect>(case_width, case_height);
	SDL_RenderFillRects(this->renderer_, white_squares.data(), nb_rect);
	SDL_RenderPresent(this->renderer_);
}

void Application::load_assets() 
{
	const std::string sprite_names[NB_SPRITES] = {
		"king_w.png", "king_b.png", "queen_w.png", "queen_b.png", "bishop_w.png",
		"bishop_b.png", "knight_b.png", "knight_w.png", "pawn_w.png", "pawn_b.png",
		"rock_w.png", "rock_b.png"
	};
	const auto [case_width, case_height] = this->get_case_dimensions();
	const SDL_Rect dest = {  0, 0, case_width, case_height  };
	for (int8_t i = 0; i < sprite_names->size(); ++i)
	{
		const auto surface =  IMG_Load(std::string{ "assets/" + sprite_names[i]}.c_str());
		this->sprites_[i] = SDL_CreateTextureFromSurface(this->renderer_, surface);
		SDL_FreeSurface(surface);
		SDL_RenderCopy(this->renderer_, this->sprites_[i], nullptr, &dest);
	}
	SDL_RenderPresent(this->renderer_);
}
