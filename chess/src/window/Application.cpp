#include <SDL2/SDL.h>
#include <stdexcept>
#include <array>
#include <memory>
#include "AssetFactory.h"
#include "Application.h"
#include "EventHandler.h"
#include "../game/BoardGame.h"

std::unique_ptr<EventHandler> Application::event_handler_factory(const SDL_Event& e, bool& quit)
{
	if (e.type == SDL_QUIT)
	{
		return std::make_unique<QuitHandler>(*this ,quit);
	}
	if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		return std::make_unique<MouseButtonHandler>(*this);
	}
	return nullptr;
}


void Application::app_loop()
{
	SDL_RenderPresent(this->renderer_);
	bool quit = false;
	SDL_Event e;
	while (!quit)
	{
		while (SDL_PollEvent(&e))
		{
			if (const auto handler = this->event_handler_factory(e, quit))
			{
				(*handler)(e);
			}
		}
	}
}


void Application::init()
{
	this->board_.init_game();
	this->init_window_and_renderer();
	this->draw_board();
	this->load_assets();
	this->app_loop();
}


Application::~Application()
{
	for (const auto& asset : this->assets_)
	{
		SDL_DestroyTexture(asset.texture);
	}
	SDL_DestroyRenderer(this->renderer_);
	SDL_DestroyWindow(this->window_);
	SDL_Quit();
}

void Application::render_square_asset(const Asset& asset, const CaseColor& color ) const noexcept
{
	SDL_SetRenderDrawColor(this->renderer_, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(this->renderer_, &asset.rect);
	SDL_RenderCopy(this->renderer_, asset.texture, nullptr, &asset.rect);
}

void Application::render_legal_squares(const Piece& piece) const noexcept
{
	for (const auto square : piece.get_legal_squares())
	{
		if (!square) continue;
		auto rect = this->get_rect_of_square(*square);
		SDL_SetRenderDrawColor(this->renderer_, 55, 205, 0, 255);
		SDL_RenderFillRect(this->renderer_, &rect);
	}
}

void Application::set_current_asset(Asset* asset) noexcept
{
	if (this->current_asset_ == asset) return;
	if (this->current_asset_)
	{
		this->render_square_asset(
			*this->current_asset_,
			this->get_square_case_color(*this->current_asset_->piece.get_square())
		);
	}
	this->render_square_asset(*asset, { 255,205,0,255 });
	// this->render_legal_squares(asset->piece);
	SDL_RenderPresent(this->renderer_);
	this->current_asset_ = asset;
}

const CaseColor& Application::get_square_case_color(const Square& square) const noexcept
{
	if ((square.get_file() + square.get_rank()) % 2)
	{
		return this->primary_color_;
	}
	return this->secondary_color_;
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
}

void Application::load_assets() 
{
	for (const auto& color: this->board_.get_colors())
	{
		color->accept(AssetFactory(*this));
	}
}

SDL_Rect Application::get_rect_of_square(const Square& square) const noexcept
{
	const auto [case_width, case_height] = this->get_case_dimensions();
	return {  square.get_file() * case_width, square.get_rank() * case_height, case_width, case_height  };
}

