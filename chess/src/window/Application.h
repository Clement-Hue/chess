#pragma once
#include <SDL2/SDL.h>
#include <memory>
#include "EventHandler.h"
#include "../game/BoardGame.h"
#include "../Common.h"
#include "Renderer.h"
#include "Types.h"


class CHESS_API Application
{
public:
	explicit Application(WindowSize window_size = { 800,800 },
		CaseColor primary_color = { 180, 255, 255,255 }
	, CaseColor secondary_color = { 255, 255, 255, 255 });
	~Application();
	Application(const Application&) = delete;
	Application(Application&&) = delete;
	Application& operator=(const Application&) = delete;
	Application& operator=(Application&&) = delete;

	void init();
	const Asset* get_current_selection() const noexcept { return this->current_selection_; }
	void set_current_selection(const Asset* asset) noexcept;
	BoardGame& get_board() noexcept { return this->board_; }
	Renderer& get_renderer() const noexcept { return *this->renderer_; };
private:
	std::unique_ptr<Renderer> renderer_{nullptr};
	const Asset* current_selection_{nullptr};
	const WindowSize window_size_;
	const CaseColor primary_color_;
	const CaseColor secondary_color_;
	SDL_Window* window_{ nullptr };
	BoardGame board_;

	MouseButtonHandler mouse_button_handler_{*this};

	void init_window_and_renderer();
	void app_loop();
	EventHandler* get_event_handler(const SDL_Event&);
};

