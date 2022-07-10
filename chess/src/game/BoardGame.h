#pragma once
#include "Piece.h"
#include "Square.h"
#include <vector>
#include "Common.h"
#include <memory>


class CHESS_API  BoardGame
{
	using pieces_type = std::vector<std::unique_ptr<Piece>>;
	struct Pieces
	{
		pieces_type black;
		pieces_type white;
	};
public:
	BoardGame();
	BoardGame(const BoardGame&) = delete;
	BoardGame(BoardGame&&) = delete;
	BoardGame& operator=(const BoardGame&) = delete;
	BoardGame& operator=(BoardGame&&) = delete;
	Square& operator[](const uint8_t i) noexcept { return this->squares_[i]; }
	~BoardGame() = default;
	void init_game() noexcept;
private:
	std::vector<Square> squares_;
	Pieces pieces_;
	pieces_type& get_pieces(const PieceColor color) noexcept
	{
		return color == PieceColor::black ? this->pieces_.black : this->pieces_.white;
	}
	void init_valuable_pieces(PieceColor, uint8_t) noexcept;
	void init_pawns(PieceColor, uint8_t) noexcept;
};

