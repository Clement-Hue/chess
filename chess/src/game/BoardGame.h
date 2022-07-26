#pragma once
#include <vector>
#include <memory>
#include "Common.h"
#include "Square.h"
#include "PieceColor.h"


class CHESS_API  BoardGame
{
public:
	BoardGame();
	BoardGame(const BoardGame&) = delete;
	BoardGame(BoardGame&&) = delete;
	BoardGame& operator=(const BoardGame&) = delete;
	BoardGame& operator=(BoardGame&&) = delete;
	Square& operator[](const int8_t i) noexcept { return this->squares_[i]; }
	~BoardGame() = default;
	void init_game() noexcept;
	bool has_square_value(const int8_t value) const noexcept { return value >= 0 && value < squares_.size(); }
	PieceColor& get_color(const int8_t i) const  noexcept { return *this->colors_[i]; }
private:
	std::vector<Square> squares_;
	std::unique_ptr<PieceColor> colors_[2]  { std::make_unique<WhiteColor>(*this), std::make_unique<BlackColor>(*this) };
};

