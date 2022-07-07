#pragma once
#include <SDL2/SDL.h>
#include "BoardGame.h"
#include "EventHandler.h"
#include <memory>

struct WindowSize
{
	const int width, height;
};

struct CaseColor
{
	uint8_t r, g, b, a;
};
class Application
{
public:
	explicit Application(const WindowSize window_size = {800,800},
		const CaseColor primary_color = { 180, 255, 255,255 }
		, const CaseColor secondary_color = { 255, 255, 255, 255 }) :
	window_size_(window_size),primary_color_(primary_color), secondary_color_(secondary_color) {}
	void init();
	Application(const Application&) = delete;
	Application(Application&&) = delete;
	Application& operator=(const Application&) = delete;
	Application& operator=(Application&&) = delete;
	~Application();
private:
	const WindowSize window_size_;
	const CaseColor primary_color_;
	const CaseColor secondary_color_;
	SDL_Window* window_{ nullptr };
	SDL_Renderer* renderer_{ nullptr };
	BoardGame board_;

	void init_window_and_renderer();
	void draw_board() const noexcept;
	void app_loop();
	std::unique_ptr<EventHandler> event_handler_factory(const SDL_Event&, bool&);
};

