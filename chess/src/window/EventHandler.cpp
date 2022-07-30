#include "EventHandler.h"
#include <SDL2/SDL.h>

#include "Application.h"
#include "Renderer.h"


void MouseButtonHandler::operator()(const SDL_Event& e) noexcept
{
	if ( const auto asset = this->app_.get_renderer().get_asset_of_coordinates(e.button.x, e.button.y);
		asset && asset->piece.get_color().is_turn())
	{
		this->app_.set_current_selection(asset);
		return;
	}
	if (const auto asset = this->app_.get_current_selection())
	{
		const auto next_square = this->get_square_of_coordinates(e.button.x, e.button.y);
		const auto prev_square = asset->piece.get_square();
		this->app_.get_renderer().clear_legal_squares(*asset);
		if (asset->piece.move(*next_square))
		{
			this->app_.get_renderer().render_square(*prev_square);
			this->app_.get_renderer().render_square(*next_square);
		}
		this->app_.get_renderer().update_screen();
	}

}

Square* MouseButtonHandler::get_square_of_coordinates(const int x, const int y) const noexcept
{
	const auto [case_width, case_height] = this->app_.get_renderer().get_case_dimensions();
	const int8_t rank = y / case_height;
	const int8_t file = x / case_width;
	const int8_t square_value = rank * 8 + file;
	return &this->app_.get_board()[square_value];
}

