#pragma once
#include <vector>
#include "Square.h"
class BoardGame
{
public:
	BoardGame();
	const std::vector<Square>& get_squares() const noexcept { return this->squares_; }
private:
	std::vector<Square> squares_{};
};

