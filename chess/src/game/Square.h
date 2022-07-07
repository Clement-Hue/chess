#pragma once
#include <cstdint>

class Piece;

struct Square
{
	uint8_t value;
	Piece* piece{ nullptr };
};

