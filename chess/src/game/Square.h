#pragma once
#include <cstdint>
#include "Common.h"

class  Piece;

struct CHESS_API Square
{
	const uint8_t value;
	Piece* piece{ nullptr };
	bool operator==(const Square& other) const noexcept
	{
		return other.value == this->value;
	}
};

