#include "Renderer.h"
#include "../game/Constants.h"


Renderer::Renderer(BoardGame& board, SDL_Window& window, const WindowSize window_size, const CaseColor primary_color, const CaseColor secondary_color):
 renderer_( SDL_CreateRenderer(&window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) ),
		primary_color_(primary_color), secondary_color_(secondary_color),
		window_size_(window_size), board_(board) 
{
	for (const auto& color: this->board_.get_colors())
	{
		color->accept(AssetFactory(*this));
	}
}

Renderer::~Renderer()
{
	for (const auto& asset : this->assets_)
	{
		SDL_DestroyTexture(asset.texture);
	}
	SDL_DestroyRenderer(this->renderer_);
}

void Renderer::render_board() const noexcept
{
	for (const auto& square: this->board_.get_squares())
	{
		this->render_square(square);
	}
}

std::tuple<int, int> Renderer::get_case_dimensions() const noexcept
{
	return { this->window_size_.width / NB_COLUMNS, this->window_size_.height / NB_COLUMNS };
}

void Renderer::render_square(const Square& square) const noexcept
{
	this->render_square(square, this->get_square_case_color(square));
}

void Renderer::render_square(const Square& square, const CaseColor color) const noexcept
{
	SDL_SetRenderDrawBlendMode(this->renderer_, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(this->renderer_, color.r, color.g, color.b, color.a);
	const SDL_Rect rect = this->get_rect_of_square(square);
	SDL_RenderFillRect(this->renderer_, &rect);
	if (const auto piece = square.get_piece())
	{
		if (const auto asset = this->get_asset_of_piece(*piece))
		{
			this->render_asset(*asset);
		}
	}
}

void Renderer::render_asset(const Asset& asset) const noexcept
{
	const auto square = asset.piece.get_square();
	if (!square) return;
	const auto rect = this->get_rect_of_square(*square);
	SDL_RenderCopy(this->renderer_, asset.texture, nullptr, &rect);
}

void Renderer::render_squares(const std::vector<Square*>& squares) const noexcept
{
	for (const Square* square : squares)
	{
		if (!square) continue;
		this->render_square(*square);
	}
}


void Renderer::render_squares(const std::vector<Square* >& squares, const CaseColor color) const noexcept
{
	for (const Square* square : squares)
	{
		if (!square) continue;
		this->render_square(*square, color) ;
	}
}

void Renderer::render_selection(const Asset& asset) const noexcept
{
	this->render_square(*asset.piece.get_square(), {255, 205,0 ,255});
}

void Renderer::clear_selection(const Asset& asset) const noexcept
{
	this->render_square(*asset.piece.get_square());
}


void Renderer::update_screen() const noexcept
{
	SDL_RenderPresent(this->renderer_);
}

void Renderer::add_asset(Piece& piece,SDL_Surface& surface) noexcept
{
	SDL_Texture* texture = SDL_CreateTextureFromSurface(this->renderer_, &surface);
	this->assets_.emplace_back(Asset{ piece, texture });
}

const Asset* Renderer::get_asset_of_coordinates(const int x, const int y)  const noexcept
{
	for (const auto& asset : this->assets_)
	{
		const auto square = asset.piece.get_square();
		if (!square) continue;
		const SDL_Rect rect = this->get_rect_of_square(*square);
		if (x > rect.x && x < rect.x + rect.w && y > rect.y && y < rect.y + rect.h)
		{
			return &asset;
		}
	}
	return nullptr;
}

void Renderer::render_assets() const noexcept
{
	for (const auto& asset: this->assets_)
	{
		this->render_asset(asset);
	}
}

SDL_Rect Renderer::get_rect_of_square(const Square& square) const noexcept
{
	const auto [case_width, case_height] = this->get_case_dimensions();
	return {  square.get_file() * case_width, square.get_rank() * case_height, case_width, case_height  };
}

const Asset* Renderer::get_asset_of_piece(const Piece& piece) const noexcept
{
	for (auto& asset: this->assets_)
	{
		if (&asset.piece == &piece)
		{
			return &asset;
		}
	}
	return nullptr;
}

const CaseColor& Renderer::get_square_case_color(const Square& square) const noexcept
{
	if ((square.get_file() + square.get_rank()) % 2)
	{
		return this->primary_color_;
	}
	return this->secondary_color_;
}

