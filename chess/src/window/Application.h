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
	explicit Application(const WindowSize window_size = { 800,800 },
		const CaseColor primary_color = { 180, 255, 255,255 }
		, const CaseColor secondary_color = { 255, 255, 255, 255 }) :
	window_size_(window_size),primary_color_(primary_color), secondary_color_(secondary_color) {}
	~Application();
	Application(const Application&) = delete;
	Application(Application&&) = delete;
	Application& operator=(const Application&) = delete;
	Application& operator=(Application&&) = delete;

	void init();
	Asset* get_current_selection() const noexcept { return this->current_selection_; }
	void set_current_selection(Asset* asset) noexcept;
	BoardGame& get_board() noexcept { return this->board_; }
	Renderer& get_renderer() const noexcept;
private:
	std::unique_ptr<Renderer> renderer_{nullptr};
	Asset* current_selection_{nullptr};
	const WindowSize window_size_;
	const CaseColor primary_color_;
	const CaseColor secondary_color_;
	SDL_Window* window_{ nullptr };
	BoardGame board_;

	void init_window_and_renderer();
	void load_assets() const noexcept;
	void app_loop();
	std::unique_ptr<EventHandler> event_handler_factory(const SDL_Event&, bool&);
};

