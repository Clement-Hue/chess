#pragma once
#include <SDL2/SDL.h>
#include "../game/Piece.h"
#include "../game/PieceColor.h"
#include "Application.h"


using surfaces_type = std::array<SDL_Surface*, Application::NB_SURFACES>;
class PieceAssetFactory: public PieceVisitor
{
public:
	PieceAssetFactory(Application& app, surfaces_type& surfaces ): app_(app), surfaces_(surfaces) {}
	void create_asset(Piece& piece, SDL_Surface* surface) const noexcept;
protected:
	Application& app_;
	surfaces_type& surfaces_;
};

class BlackAssetFactory final: public PieceAssetFactory
{
public:
	BlackAssetFactory(Application& app, surfaces_type& surfaces);
	void visit(Bishop& piece) const override
	{
		this->create_asset(piece, this->surfaces_[5]);
	}
	void visit(King& piece) const override
	{
		this->create_asset(piece, this->surfaces_[1]);
	}
	void visit(Knight& piece) const override
	{
		this->create_asset(piece, this->surfaces_[7]);
	}
	void visit(Pawn& piece) const override
	{
		this->create_asset(piece, this->surfaces_[9]);
	}
	void visit(Queen& piece) const override
	{
		this->create_asset(piece, this->surfaces_[3]);
	}
	void visit(Rock& piece) const override
	{
		this->create_asset(piece, this->surfaces_[11]);
	}
};


class WhiteAssetFactory final: public PieceAssetFactory
{
public:
	WhiteAssetFactory(Application& app, surfaces_type& surfaces): PieceAssetFactory(app, surfaces) {}
	void visit(Bishop& piece) const override
	{
		this->create_asset(piece, this->surfaces_[4]);
	}
	void visit(King& piece) const override
	{
		this->create_asset(piece, this->surfaces_[0]);
	}
	void visit(Knight& piece) const override
	{
		this->create_asset(piece, this->surfaces_[6]);
	}
	void visit(Pawn& piece) const override
	{
		this->create_asset(piece, this->surfaces_[8]);
	}
	void visit(Queen& piece) const override
	{
		this->create_asset(piece, this->surfaces_[2]);
	}
	void visit(Rock& piece) const override
	{
		this->create_asset(piece, this->surfaces_[10]);
	}
};

class AssetFactory final: public ColorVisitor
{
public:
	AssetFactory(Application& app, surfaces_type& surfaces): app_(app), surfaces_(surfaces) {}
	template <typename Factory>
	void create_pieces_assets(PieceColor& color) const noexcept
	{
		for (const auto& piece: color.get_pieces())
		{
			piece->accept(Factory(this->app_, this->surfaces_));
		}
	}
	void visit(BlackColor& color) const override
	{
		this->create_pieces_assets<BlackAssetFactory>(color);
	}
	void visit(WhiteColor& color) const override
	{
		this->create_pieces_assets<WhiteAssetFactory>(color);
	}
private:
	Application& app_;
	surfaces_type& surfaces_;
};

