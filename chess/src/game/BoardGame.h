#pragma once
#include <vector>
#include <memory>
#include "Common.h"
#include "Piece.h"
#include "Square.h"


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
	bool has_square_value(const int8_t value) const noexcept { return value >= 0 && value < squares_.size(); }
private:
	std::vector<Square> squares_;
	Pieces pieces_;
	template <typename Color>
	pieces_type& get_pieces()  noexcept = delete;
	template <typename Color>
	void init_valuable_pieces() noexcept;
	template <typename Color>
	void init_pawns() noexcept;
};

template <>
inline BoardGame::pieces_type& BoardGame::get_pieces<BlackColor>() noexcept
{
	return this->pieces_.black;
}

template <>
inline BoardGame::pieces_type& BoardGame::get_pieces<WhiteColor>() noexcept
{
	return this->pieces_.white;
}

