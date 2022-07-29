#pragma once
#include <SDL2/SDL.h>
#include <memory>
#include "EventHandler.h"
#include "../game/BoardGame.h"
#include "../Common.h"

struct Asset
{
	Piece& piece;
	SDL_Texture* texture;
	SDL_Rect rect;
};

struct WindowSize
{
	const int width, height;
};

struct CaseColor
{
	uint8_t r, g, b, a;
};
class CHESS_API Application
{
public:
	explicit Application(const WindowSize window_size = { 800,800 },
		const CaseColor primary_color = { 180, 255, 255,255 }
		, const CaseColor secondary_color = { 255, 255, 255, 255 }) :
	window_size_(window_size),primary_color_(primary_color), secondary_color_(secondary_color) {}
	void init();
	Application(const Application&) = delete;
	Application(Application&&) = delete;
	Application& operator=(const Application&) = delete;
	Application& operator=(Application&&) = delete;
	std::vector<Asset>& get_assets() noexcept { return this->assets_; }
	~Application();
	Asset* get_current_asset() const noexcept { return this->current_asset_; }
	void set_current_asset(Asset* asset) noexcept;
	SDL_Renderer* get_renderer() const noexcept { return this->renderer_; }
	std::tuple<int, int> get_case_dimensions() const noexcept
	{
		return { this->window_size_.width / NB_COLUMNS, this->window_size_.height / NB_COLUMNS };
	}
	const CaseColor& get_square_case_color(const Square& square) const noexcept;
	SDL_Rect get_rect_of_square(const Square& square) const noexcept;
private:
	Asset* current_asset_{nullptr};
	const WindowSize window_size_;
	const CaseColor primary_color_;
	const CaseColor secondary_color_;
	std::vector<Asset> assets_;
	SDL_Window* window_{ nullptr };
	SDL_Renderer* renderer_{ nullptr };
	BoardGame board_;
	void init_window_and_renderer();
	void draw_board() const noexcept;
	void load_assets() ;
	void app_loop();
	void render_square_asset(const Asset&, const CaseColor&) const noexcept;
	void render_legal_squares(const Piece& piece) const noexcept;
	std::unique_ptr<EventHandler> event_handler_factory(const SDL_Event&, bool&);
};

