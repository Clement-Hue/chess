#include "Application.h"
#include <SDL2/SDL.h>
#include <stdexcept>
#include <array>
#include <memory>
#include "AssetFactory.h"
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
	this->load_assets();
	this->renderer_->render_board();
	this->renderer_->update_screen();
	this->app_loop();
}

Application::~Application()
{
	SDL_DestroyWindow(this->window_);
	SDL_Quit();
}

void Application::set_current_selection(const Asset* asset)  noexcept
{
	if (this->current_selection_ == asset) return;
	if (this->current_selection_)
	{
		this->renderer_->clear_selection(*this->current_selection_);
		this->renderer_->render_squares(this->current_selection_->piece.get_squares_of_legal_moves());
	}
	this->renderer_->render_selection(*asset);
	this->renderer_->render_squares(asset->piece.get_squares_of_legal_moves(), {55,205,0,100} );
	this->renderer_->update_screen();
	this->current_selection_ = asset;
}

Renderer& Application::get_renderer() const noexcept
{
	return *this->renderer_; 
}

void Application::init_window_and_renderer()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	this->window_ = SDL_CreateWindow("Chess", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, this->window_size_.width, this->window_size_.height,
		SDL_WINDOW_RESIZABLE);
	if (this->window_ == nullptr)
	{
		throw std::runtime_error("Unable to create the window");
	}
	this->renderer_ = std::make_unique<Renderer>(this->board_,*this->window_, this->window_size_, this->primary_color_, this->secondary_color_);
}

void Application::load_assets()  const noexcept
{
	for (const auto& color: this->board_.get_colors())
	{
		color->accept(AssetFactory(*this->renderer_));
	}
}

