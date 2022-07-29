#include "SDL2/SDL_image.h"
#include "AssetFactory.h"
#include <string>

static PieceAssetFactory::surfaces_type create_surfaces(const std::array<std::string, PieceAssetFactory::NB_SURFACES>& sprite_names)
{
	PieceAssetFactory::surfaces_type surfaces{nullptr};
	for (int8_t i = 0; i < surfaces.size(); ++i)
	{
		surfaces[i] =  IMG_Load(std::string{ "assets/" + sprite_names[i]}.c_str());
	}
	return surfaces;
}


void PieceAssetFactory::create_asset(Piece& piece, SDL_Surface* surface) const noexcept
{
	this->renderer_.add_asset(piece, *surface);
}


void clear_surfaces(const PieceAssetFactory::surfaces_type& surfaces)
{
	for (const auto& surface: surfaces)
	{
		SDL_FreeSurface(surface);
	}
}

void AssetFactory::create_piece_assets(PieceAssetFactory::surfaces_type& surfaces, PieceColor& color ) const noexcept
{
	for (const auto& piece: color.get_pieces())
	{
		piece->accept(PieceAssetFactory(this->renderer_, surfaces));
	}
}

void AssetFactory::visit(BlackColor& color) const
{
	auto surfaces = create_surfaces({
		"king_b.png", "queen_b.png",
		"bishop_b.png",  "knight_b.png", "pawn_b.png",
		 "rock_b.png"
		});
	this->create_piece_assets(surfaces , color);
	clear_surfaces(surfaces);
}

void AssetFactory::visit(WhiteColor& color) const
{
	auto surfaces = create_surfaces({
		"king_w.png", "queen_w.png",
		"bishop_w.png",  "knight_w.png", "pawn_w.png",
		 "rock_w.png"
		});
	this->create_piece_assets(surfaces , color);
	clear_surfaces(surfaces);
}
