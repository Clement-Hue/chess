#pragma once
#include <SDL2/SDL.h>
#include "../game/Piece.h"
#include "../game/PieceColor.h"
#include "Renderer.h"


class PieceAssetFactory final: public PieceVisitor
{
public:
	static constexpr int8_t NB_SURFACES = 6;
	using surfaces_type = std::array<SDL_Surface*, NB_SURFACES>;
	PieceAssetFactory(Renderer& renderer, surfaces_type& surfaces): renderer_(renderer), surfaces_(surfaces) {}
	void create_asset(Piece& piece, SDL_Surface* surface) const noexcept;
	void visit(Bishop& piece) const override
	{
		this->create_asset(piece, this->surfaces_[2]);
	}
	void visit(King& piece) const override
	{
		this->create_asset(piece, this->surfaces_[0]);
	}
	void visit(Knight& piece) const override
	{
		this->create_asset(piece, this->surfaces_[3]);
	}
	void visit(Pawn& piece) const override
	{
		this->create_asset(piece, this->surfaces_[4]);
	}
	void visit(Queen& piece) const override
	{
		this->create_asset(piece, this->surfaces_[1]);
	}
	void visit(Rock& piece) const override
	{
		this->create_asset(piece, this->surfaces_[5]);
	}
protected:
	Renderer& renderer_;
	surfaces_type& surfaces_;
};

class AssetFactory final: public ColorVisitor
{
public:
	AssetFactory(Renderer& renderer): renderer_(renderer) {}
	void create_piece_assets(PieceAssetFactory::surfaces_type& surfaces,PieceColor& color) const noexcept;
	void visit(BlackColor& color) const override;
	void visit(WhiteColor& color) const override;
private:
	Renderer& renderer_;
};

