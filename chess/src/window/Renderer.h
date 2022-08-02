#pragma once
#include <SDL2/SDL.h>
#include <tuple>
#include "../game/Piece.h"
#include "../game/BoardGame.h"
#include "AssetFactory.h"
#include "Types.h"


class Renderer
{
public:
	Renderer(BoardGame& board, SDL_Window& window, WindowSize window_size,
		CaseColor primary_color,  CaseColor secondary_color);
	~Renderer();
	Renderer(const Renderer&) = delete;
	Renderer(Renderer&&) = delete;
	Renderer& operator=(Renderer&&) = delete;
	Renderer& operator=(const Renderer&) = delete;

	void render_board() const noexcept;
	std::tuple<int, int> get_case_dimensions() const noexcept;
	void render_selection(const Asset& asset) const noexcept;
	void render_squares(const std::vector<Square*>& squares, CaseColor color) const noexcept;
	void render_squares(const std::vector<Square*>& squares) const noexcept;
	void clear_selection(const Asset& asset) const noexcept;
	void render_square(const Square& square) const noexcept;
	void render_square(const Square& square, CaseColor color) const noexcept;
	void render_asset(const Asset& asset) const noexcept;
	void update_screen() const noexcept;
	void add_asset(Piece& piece, SDL_Surface& surface)  noexcept;
	std::vector<Asset>& get_assets() noexcept { return this->assets_; }
	const Asset* get_asset_of_coordinates(int x, int y) const noexcept;
	void render_assets() const noexcept;
	void add_asset_factory(std::unique_ptr<PieceAssetFactory> factory, PieceColor& color) noexcept;
private:
	SDL_Renderer* renderer_;
	CaseColor primary_color_;
	CaseColor secondary_color_;
	WindowSize window_size_;
	std::vector<Asset> assets_;
	BoardGame& board_;
	std::vector<std::unique_ptr<PieceAssetFactory>> asset_factories_;

	const Asset* get_asset_of_piece(const Piece& piece) const  noexcept;
	const CaseColor& get_square_case_color(const Square& square) const noexcept;
	SDL_Rect get_rect_of_square(const Square& square) const noexcept;
};

