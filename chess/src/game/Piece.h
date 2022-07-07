#pragma once
#include "Square.h"
#include <vector>

class Piece
{
public:
	explicit Piece(Square& square): square_(square) {}
	virtual std::vector<uint8_t> available_square() const noexcept = 0;
	void move(Square& square) noexcept;
	Piece(const Piece&) = delete;
	Piece(Piece&&) = delete;
	Piece& operator=(const Piece&) = delete;
	Piece& operator=(Piece&&) = delete;
	virtual ~Piece() = default;
protected:
	Square& square_;
};

class Rock final: public Piece
{
public:
	explicit Rock(Square& square): Piece(square) {}
	std::vector<uint8_t> available_square() const noexcept override;	
};
