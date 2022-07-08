#pragma once
#include "Square.h"
#include <vector>
#include "BoardGame.h"
#include "Common.h"

enum class CHESS_API Color { white, black };

class CHESS_API Piece
{
public:
	explicit Piece(BoardGame& board, Square& square, Color color);
	virtual std::vector<Square*> available_square() const noexcept = 0;
	void move(Square& square) noexcept;
	Piece(const Piece&) = delete;
	Piece(Piece&&) = delete;
	Piece& operator=(const Piece&) = delete;
	Piece& operator=(Piece&&) = delete;
	virtual ~Piece() = default;
	const Square* get_square() const noexcept { return this->square_; }
	Color get_color() const noexcept { return this->color_; }
protected:
	BoardGame& board_;
	Square* square_{nullptr};
	Color color_;
};

class CHESS_API Rock final: public Piece
{
public:
	explicit Rock(BoardGame& board,Square& square, const Color color): Piece(board, square, color) {}
	std::vector<Square*> available_square() const noexcept override;	
};
