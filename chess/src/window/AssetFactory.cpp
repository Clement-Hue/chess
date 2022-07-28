#include "SDL2/SDL_image.h"
#include "AssetFactory.h"
#include <string>

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

PieceAssetFactory::~PieceAssetFactory()
{
	for (const auto& surface: this->surfaces_)
	{
		SDL_FreeSurface(surface);
	}
}

static  PieceAssetFactory::surfaces_type create_surfaces(const std::array<std::string, PieceAssetFactory::NB_SURFACES>& sprite_names)
{
	PieceAssetFactory::surfaces_type surfaces{nullptr};
	for (int8_t i = 0; i < surfaces.size(); ++i)
	{
		surfaces[i] =  IMG_Load(std::string{ "assets/" + sprite_names[i]}.c_str());
	}
	return surfaces;
}

BlackAssetFactory::BlackAssetFactory(Application& app): PieceAssetFactory(app, 
	create_surfaces( {
		"king_b.png", "queen_b.png", 
		"bishop_b.png",  "knight_b.png", "pawn_b.png",
		 "rock_b.png"
	})) 
{
}

WhiteAssetFactory::WhiteAssetFactory(Application& app): PieceAssetFactory(app, 
	create_surfaces({
		"king_w.png", "queen_w.png", 
		"bishop_w.png",  "knight_w.png", "pawn_w.png",
		 "rock_w.png"
	})
	)
{
}
