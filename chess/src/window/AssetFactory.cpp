#include "AssetFactory.h"

void PieceAssetFactory::create_asset(Piece& piece, SDL_Surface* surface) const noexcept
{
	const auto [case_width, case_height] = this->app_.get_case_dimensions();
	const SDL_Rect dest = {  piece.get_square()->get_file() * case_width, piece.get_square()->get_rank() * case_height, case_width, case_height  };
	SDL_Texture* const texture = SDL_CreateTextureFromSurface(this->app_.renderer_, surface);
	this->app_.assets_.emplace_back(Asset{
		piece, texture, dest
		});
	SDL_RenderCopy(this->app_.renderer_, texture, nullptr, &dest);
}

BlackAssetFactory::BlackAssetFactory(Application& app, surfaces_type& surfaces) : PieceAssetFactory(app, surfaces)
{
}
