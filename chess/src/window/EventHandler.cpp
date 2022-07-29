#include "EventHandler.h"
#include <SDL2/SDL.h>

#include "Application.h"
#include "Renderer.h"


void MouseButtonHandler::operator()(const SDL_Event& e) noexcept
{
	if (const auto asset = this->get_selected_asset(e))
	{
		this->app_.set_current_selection(asset);
		return;
	}
	/*
	if (const auto asset = this->app_.get_current_selection())
	{
		const auto square = this->get_square_of_position(e.button.x, e.button.y);
		asset->piece.move(*square);
	}
	*/

}

Asset* MouseButtonHandler::get_selected_asset(const SDL_Event& e) const noexcept
{
	for (auto& asset : this->app_.get_renderer().get_assets())
	{
		if (e.button.x > asset.rect.x && e.button.x < asset.rect.x + asset.rect.w &&
			e.button.y > asset.rect.y && e.button.y < asset.rect.y + asset.rect.h)
		{
			return &asset;
		}
	}
	return nullptr;
}

Square* MouseButtonHandler::get_square_of_position(int x, int y) const noexcept
{
	const auto [case_width, case_height] = this->app_.get_renderer().get_case_dimensions();
	const int8_t rank = y / case_height;
	const int8_t file = x / case_width;
	const int8_t square_value = rank * 8 + file;
	return &this->app_.get_board()[square_value];
}

