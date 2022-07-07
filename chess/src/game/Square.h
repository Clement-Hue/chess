#pragma once
#include <cstdint>

class Piece;

struct Square
{
	const uint8_t value;
	Piece* piece{ nullptr };
};

