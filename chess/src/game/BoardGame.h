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
		pieces_type& operator[](const PieceColor color) noexcept
		{
			return color == PieceColor::black ? this->black : this->white;
		}
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
	bool has_square_value(const int8_t value) const noexcept { return value >= 0 && value < squares_.size(); }
private:
	std::vector<Square> squares_;
	Pieces pieces_;
	void init_valuable_pieces(PieceColor, uint8_t) noexcept;
	void init_pawns(PieceColor, uint8_t) noexcept;
};

