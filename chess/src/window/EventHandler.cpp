#include "EventHandler.h"
#include <SDL2/SDL.h>

#include "Application.h"


void MouseButtonHandler::operator()(const SDL_Event& e) noexcept
{
	if (const auto asset = this->get_selected_asset(e))
	{
		this->app_.set_current_asset(asset);
	}
}

Asset* MouseButtonHandler::get_selected_asset(const SDL_Event& e) const noexcept
{
	for (auto& asset : this->app_.get_assets())
	{
		if (e.button.x > asset.rect.x && e.button.x < asset.rect.x + asset.rect.w &&
			e.button.y > asset.rect.y && e.button.y < asset.rect.y + asset.rect.h)
		{
			return &asset;
		}
	}
	return nullptr;
}

