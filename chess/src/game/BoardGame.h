#pragma once
#include "Square.h"
#include <vector>
#include "Common.h"

class CHESS_API  BoardGame
{
public:
	BoardGame();
	BoardGame(const BoardGame&) = delete;
	BoardGame(BoardGame&&) = delete;
	BoardGame& operator=(const BoardGame&) = delete;
	BoardGame& operator=(BoardGame&&) = delete;
	Square& operator[](const uint8_t i) noexcept { return this->square_[i]; }
	~BoardGame() = default;
private:
	std::vector<Square> square_;
};

