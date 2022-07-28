#pragma once
#include <SDL2/SDL.h>
#include "../game/Piece.h"
#include "../game/PieceColor.h"
#include "Application.h"


class PieceAssetFactory: public PieceVisitor
{
public:
	static constexpr int8_t NB_SURFACES = 6;
	using surfaces_type = std::array<SDL_Surface*, NB_SURFACES>;
	PieceAssetFactory(Application& app, const surfaces_type& surfaces ): app_(app), surfaces_(surfaces) {}
	PieceAssetFactory(const PieceAssetFactory&) = delete;
	PieceAssetFactory(PieceAssetFactory&&) = delete;
	PieceAssetFactory& operator=(const PieceAssetFactory&) = delete;
	PieceAssetFactory& operator=(PieceAssetFactory&&) = delete;
	void create_asset(Piece& piece, SDL_Surface* surface) const noexcept;
	~PieceAssetFactory() override;
protected:
	Application& app_;
	const surfaces_type& surfaces_;
};

class BlackAssetFactory final: public PieceAssetFactory
{
public:
	BlackAssetFactory(Application& app);
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
};


class WhiteAssetFactory final: public PieceAssetFactory
{
public:
	WhiteAssetFactory(Application& app);
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
};

class AssetFactory final: public ColorVisitor
{
public:
	AssetFactory(Application& app): app_(app) {}
	template <typename Factory>
	void create_piece_assets(PieceColor& color) const noexcept
	{
		for (const auto& piece: color.get_pieces())
		{
			piece->accept(Factory(this->app_));
		}
	}
	void visit(BlackColor& color) const override
	{
		this->create_piece_assets<BlackAssetFactory>(color);
	}
	void visit(WhiteColor& color) const override
	{
		this->create_piece_assets<WhiteAssetFactory>(color);
	}
private:
	Application& app_;
};

