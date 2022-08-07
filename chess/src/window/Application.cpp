#include "Application.h"
#include <SDL2/SDL.h>
#include <stdexcept>
#include <memory>
#include "AssetFactory.h"
#include "EventHandler.h"
#include "../game/BoardGame.h"

Application::Application(const WindowSize window_size, const CaseColor primary_color, const CaseColor secondary_color):
	window_size_(window_size),primary_color_(primary_color), secondary_color_(secondary_color) 
{
	this->init_window_and_renderer();
}

EventHandler* Application::get_event_handler(const SDL_Event& e)
{
	if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		return &this->mouse_button_handler_;
	}
	return nullptr;
}

void Application::app_loop()
{
	bool quit = false;
	SDL_Event e;
	while (!quit)
	{
		while (SDL_WaitEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
				break;
			} 
			if (const auto handler = this->get_event_handler(e))
			{
				(*handler)(e);
			}
		}
	}
}

void Application::init()
{
	this->board_.init_game();
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
