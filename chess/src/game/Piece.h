#pragma once
#include "Square.h"
#include <array>
#include "BoardGame.h"
#include "Constants.h"
#include "Common.h"

enum class CHESS_API PieceColor { white, black };

class CHESS_API Piece
{
public:
	explicit Piece(BoardGame& board, Square& square, PieceColor color);
	virtual std::array<Square*,NB_SQUARES> get_eligible_squares() const noexcept = 0;
	void move(Square& square) noexcept;
	Piece(const Piece&) = delete;
	Piece(Piece&&) = delete;
	Piece& operator=(const Piece&) = delete;
	Piece& operator=(Piece&&) = delete;
	virtual ~Piece() = default;
	void remove_square() noexcept { this->square_ = nullptr; }
	const Square* get_square() const noexcept { return this->square_; }
	PieceColor get_color() const noexcept { return this->color_; }
	bool is_enemy_of(const Piece& piece) const noexcept { return this->get_color() != piece.get_color(); }
	bool is_friend_of(const Piece& piece) const noexcept { return !this->is_enemy_of(piece); }
protected:
	BoardGame& board_;
	Square* square_{nullptr};
	PieceColor color_;
	void add_eligible_file_squares(std::array<Square*, NB_SQUARES>&) const noexcept;
	void add_eligible_row_squares(std::array<Square*, NB_SQUARES>&) const noexcept;
	void add_eligible_diagonals(std::array<Square*, NB_SQUARES>&) const noexcept;
	bool is_eligible_square(std::array<Square*, NB_SQUARES>&, int8_t) const noexcept;
};

class CHESS_API Rock final: public Piece
{
public:
	explicit Rock(BoardGame& board,Square& square, const PieceColor color): Piece(board, square, color) {}
	std::array<Square*, NB_SQUARES> get_eligible_squares() const noexcept override;	
};


class CHESS_API Bishop final: public Piece
{
public:
	explicit Bishop(BoardGame& board,Square& square, const PieceColor color): Piece(board, square, color) {}
	std::array<Square*, NB_SQUARES> get_eligible_squares() const noexcept override;	
};

class CHESS_API Queen final: public Piece
{
public:
	explicit Queen(BoardGame& board,Square& square, const PieceColor color): Piece(board, square, color) {}
	std::array<Square*,NB_SQUARES> get_eligible_squares() const noexcept override;	
};

class CHESS_API Knight final: public Piece
{
public:
	explicit Knight(BoardGame& board,Square& square, const PieceColor color): Piece(board, square, color) {}
	std::array<Square*,NB_SQUARES> get_eligible_squares() const noexcept override;	
};
