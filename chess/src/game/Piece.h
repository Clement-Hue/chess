#pragma once
#include "Square.h"
#include <array>
#include "Constants.h"
#include "Common.h"
#include <functional>

class BoardGame;

enum class CHESS_API PieceColor { black , white };

class CHESS_API Piece
{
public:
	using e_squares_type = std::array<Square*, NB_SQUARES>;
	explicit Piece(BoardGame& board, Square& square, PieceColor color);
	virtual e_squares_type get_eligible_squares() const noexcept = 0;
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
};

class CHESS_API Rock final: public Piece
{
public:
	explicit Rock(BoardGame& board,Square& square, const PieceColor color): Piece(board, square, color) {}
	e_squares_type get_eligible_squares() const noexcept override;	
};


class CHESS_API Bishop final: public Piece
{
public:
	explicit Bishop(BoardGame& board,Square& square, const PieceColor color): Piece(board, square, color) {}
	e_squares_type get_eligible_squares() const noexcept override;	
};

class CHESS_API Queen final: public Piece
{
public:
	explicit Queen(BoardGame& board,Square& square, const PieceColor color): Piece(board, square, color) {}
	e_squares_type get_eligible_squares() const noexcept override;	
};

class CHESS_API King final: public Piece
{
public:
	explicit King(BoardGame& board,Square& square, const PieceColor color): Piece(board, square, color) {}
	e_squares_type get_eligible_squares() const noexcept override;	
};


class CHESS_API Knight final: public Piece
{
public:
	explicit Knight(BoardGame& board,Square& square, const PieceColor color): Piece(board, square, color) {}
	e_squares_type get_eligible_squares() const noexcept override;	
};


class CHESS_API Pawn final: public Piece
{
public:
	explicit Pawn(BoardGame& board,Square& square, const PieceColor color): Piece(board, square, color) {}
	e_squares_type get_eligible_squares() const noexcept override;	
};

