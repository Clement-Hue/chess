#pragma once
#include "Square.h"
#include <vector>

class BoardGame
{
public:
	BoardGame();
	Square& get_squares(const uint8_t i) noexcept { return this->squares_[i]; }
private:
	std::vector<Square> squares_;
};

