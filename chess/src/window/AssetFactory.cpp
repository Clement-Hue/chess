#include "SDL2/SDL_image.h"
#include "AssetFactory.h"
#include <string>
#include "Renderer.h"

static PieceAssetFactory::surfaces_type create_surfaces(const PieceAssetFactory::sprites_names_type& sprites_names)
{
	PieceAssetFactory::surfaces_type surfaces;
	for (int8_t i = 0; i < surfaces.size(); ++i)
	{
		surfaces[i] =  IMG_Load(std::string{ "assets/" + sprites_names[i]}.c_str());
	}
	return surfaces;
}

PieceAssetFactory::PieceAssetFactory(Renderer& renderer, const sprites_names_type& sprites_names):
	renderer_(renderer), surfaces_(create_surfaces(sprites_names))
{
}

void PieceAssetFactory::create_asset(Piece& piece, SDL_Surface* surface) const noexcept
{
	this->renderer_.add_asset(piece, *surface);
}

PieceAssetFactory::~PieceAssetFactory()
{
	for (const auto& surface: this->surfaces_)
	{
		SDL_FreeSurface(surface);
	}
}

void AssetFactory::visit(BlackColor& color) const
{
	this->renderer_.add_asset_factory(
		std::make_unique<PieceAssetFactory>(this->renderer_, PieceAssetFactory::sprites_names_type{
				"king_b.png", "queen_b.png",
				"bishop_b.png",  "knight_b.png", "pawn_b.png",
				 "rock_b.png"
			}), color
	);
}

void AssetFactory::visit(WhiteColor& color) const
{
	this->renderer_.add_asset_factory(
	std::make_unique<PieceAssetFactory>(this->renderer_, PieceAssetFactory::sprites_names_type{
		"king_w.png", "queen_w.png",
		"bishop_w.png",  "knight_w.png", "pawn_w.png",
		 "rock_w.png"
			}), color
	);
}
