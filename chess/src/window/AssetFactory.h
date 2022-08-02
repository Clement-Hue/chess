#pragma once
#include <SDL2/SDL.h>
#include <string>
#include "../game/Piece.h"
#include "../game/PieceColor.h"
#include "../game/PieceObserver.h"

class Renderer;

class PieceAssetFactory final: public PieceObserver
{
public:
	static constexpr int8_t NB_SURFACES = 6;
	using surfaces_type = std::array<SDL_Surface*, NB_SURFACES>;
	using sprites_names_type = std::array<std::string, NB_SURFACES>;
	PieceAssetFactory(PieceAssetFactory&&) = delete;
	PieceAssetFactory(const PieceAssetFactory&) = delete;
	PieceAssetFactory& operator=(PieceAssetFactory&&) = delete;
	PieceAssetFactory& operator=(const PieceAssetFactory&) = delete;
	PieceAssetFactory(Renderer& renderer, const sprites_names_type& sprites_names);
	void create_asset(Piece& piece, SDL_Surface* surface) const noexcept;
	void on_add(Pawn& piece) const noexcept override
	{
		this->create_asset(piece, this->surfaces_[4]);
	}
	void on_add(Bishop& piece) const noexcept override
	{
		this->create_asset(piece, this->surfaces_[2]);
	}
	void on_add(King& piece) const noexcept override
	{
		this->create_asset(piece, this->surfaces_[0]);
	}
	void on_add(Knight& piece) const noexcept override
	{
		this->create_asset(piece, this->surfaces_[3]);
	}
	void on_add(Queen& piece) const noexcept override
	{
		this->create_asset(piece, this->surfaces_[1]);
	}
	void on_add(Rock& piece) const noexcept override
	{
		this->create_asset(piece, this->surfaces_[5]);
	}
	~PieceAssetFactory() override;
protected:
	Renderer& renderer_;
	surfaces_type surfaces_;
};


class AssetFactory final: public ColorVisitor
{
public:
	AssetFactory(Renderer& renderer): renderer_(renderer) {}
	void visit(BlackColor& color) const override;
	void visit(WhiteColor& color) const override;
private:
	Renderer& renderer_;
};

