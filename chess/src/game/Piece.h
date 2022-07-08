#pragma once
#include "Square.h"
#include <vector>
#include "BoardGame.h"
#include "Common.h"

enum class CHESS_API PieceColor { white, black };

class CHESS_API Piece
{
public:
	explicit Piece(BoardGame& board, Square& square, PieceColor color);
	virtual std::vector<Square*> get_eligible_squares() const noexcept = 0;
	void move(Square& square) noexcept;
	Piece(const Piece&) = delete;
	Piece(Piece&&) = delete;
	Piece& operator=(const Piece&) = delete;
	Piece& operator=(Piece&&) = delete;
	virtual ~Piece() = default;
	const Square* get_square() const noexcept { return this->square_; }
	PieceColor get_color() const noexcept { return this->color_; }
protected:
	BoardGame& board_;
	Square* square_{nullptr};
	PieceColor color_;
	void add_eligible_file_squares(std::vector<Square*>&) const noexcept;
	void add_eligible_row_squares(std::vector<Square*>&) const noexcept;
	void add_eligible_diagonals(std::vector<Square*>&) const noexcept;
	bool is_eligible_square(std::vector<Square*>&, int8_t) const noexcept;
};

class CHESS_API Rock final: public Piece
{
public:
	explicit Rock(BoardGame& board,Square& square, const PieceColor color): Piece(board, square, color) {}
	std::vector<Square*> get_eligible_squares() const noexcept override;	
};


class CHESS_API Bishop final: public Piece
{
public:
	explicit Bishop(BoardGame& board,Square& square, const PieceColor color): Piece(board, square, color) {}
	std::vector<Square*> get_eligible_squares() const noexcept override;	
};
