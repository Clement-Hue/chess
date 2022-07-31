#include "SDL2/SDL_image.h"
#include "AssetFactory.h"
#include <string>

class Surface
{
public:
	Surface( const std::array<std::string, PieceAssetFactory::NB_SURFACES>& sprite_names)
	{
		for (int8_t i = 0; i < this->surfaces_.size(); ++i)
		{
			this->surfaces_[i] =  IMG_Load(std::string{ "assets/" + sprite_names[i]}.c_str());
		}
	}
	~Surface()
	{
		for (const auto& surface: this->surfaces_)
		{
			SDL_FreeSurface(surface);
		}
	}
	PieceAssetFactory::surfaces_type& get() noexcept { return this->surfaces_; }
private:
	PieceAssetFactory::surfaces_type surfaces_{nullptr};
};


void PieceAssetFactory::create_asset(Piece& piece, SDL_Surface* surface) const noexcept
{
	this->renderer_.add_asset(piece, *surface);
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
	Surface surface  ({
		"king_b.png", "queen_b.png",
		"bishop_b.png",  "knight_b.png", "pawn_b.png",
		 "rock_b.png"
		});
	this->create_piece_assets(surface.get() , color);
}

void AssetFactory::visit(WhiteColor& color) const
{
	Surface surface  ({
		"king_w.png", "queen_w.png",
		"bishop_w.png",  "knight_w.png", "pawn_w.png",
		 "rock_w.png"
		});
	this->create_piece_assets(surface.get(), color);
}
