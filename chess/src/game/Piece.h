#pragma once
#include "Square.h"
#include <vector>
#include "BoardGame.h"
#include "Common.h"

class CHESS_API  Piece
{
public:
	explicit Piece(BoardGame& board, Square& square);
	virtual std::vector<Square*> available_square() const noexcept = 0;
	void move(Square& square) noexcept;
	Piece(const Piece&) = delete;
	Piece(Piece&&) = delete;
	Piece& operator=(const Piece&) = delete;
	Piece& operator=(Piece&&) = delete;
	virtual ~Piece() = default;
protected:
	BoardGame& board_;
	Square* square_;
};

class CHESS_API Rock final: public Piece
{
public:
	explicit Rock(BoardGame& board,Square& square): Piece(board, square) {}
	std::vector<Square*> available_square() const noexcept override;	
};
