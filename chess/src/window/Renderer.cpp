#include "Renderer.h"
#include "../game/Constants.h"

Renderer::~Renderer()
{
	for (const auto& asset : this->assets_)
	{
		SDL_DestroyTexture(asset.texture);
	}
	SDL_DestroyRenderer(this->renderer_);
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

void Renderer::render_board() const noexcept
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

void Renderer::render_squares(const std::array<Square*, NB_SQUARES>& squares) const noexcept
{
	for (const Square* square : squares)
	{
		if (!square) continue;
		this->render_square(*square);
	}
}


void Renderer::render_squares(const std::array<Square*, NB_SQUARES>& squares, const CaseColor color) const noexcept
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


