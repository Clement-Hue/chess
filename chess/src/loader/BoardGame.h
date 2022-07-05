#pragma once
#include <SDL2/SDL.h>
namespace loader
{
	struct CaseColor
	{
		uint8_t r, g, b, a;
	};
	class BoardGame
	{
	public:
		explicit BoardGame(const CaseColor primary_color = { 180, 255, 255,255}
			, const CaseColor secondary_color = { 255, 255, 255, 255 }) :
		primary_color_(primary_color), secondary_color_(secondary_color){}
		void create_window();
		BoardGame(const BoardGame&) = delete;
		BoardGame(BoardGame&&) = delete;
		BoardGame& operator=(const BoardGame&) = delete;
		BoardGame& operator=(BoardGame&&) = delete;
		~BoardGame();
	private:
		const CaseColor primary_color_;
		const CaseColor secondary_color_;
		void init_window_and_renderer();
		void draw_board() const noexcept;
		SDL_Window* window_{ nullptr };
		SDL_Renderer* renderer_{ nullptr };
	};
}

