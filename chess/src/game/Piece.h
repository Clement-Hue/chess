#pragma once
#include <array>
#include "Constants.h"
#include "Common.h"
#include "PieceColor.h"
#include <memory>

class BoardGame;
class Square;


class CHESS_API Piece
{
public:
	using e_squares_type = std::array<Square*, NB_SQUARES>;
	using pinning_filter_type = void (*)(Piece&);
	virtual void compute_eligible_squares() noexcept = 0;
	void move(Square& square) noexcept;
	Piece(BoardGame& board, Square& square, std::unique_ptr<PieceColor> color);
	Piece(const Piece&) = delete;
	Piece(Piece&&) = delete;
	Piece& operator=(const Piece&) = delete;
	Piece& operator=(Piece&&) = delete;
	virtual ~Piece() = default;
	void remove_square() noexcept { this->square_ = nullptr; }
	const Square* get_square() const noexcept { return this->square_; }
	PieceColor& get_color() const noexcept { return *this->color_; }
	bool is_enemy_of(const Piece& piece) const noexcept { return this->get_color() != piece.get_color(); }
	bool is_friend_of(const Piece& piece) const noexcept { return !this->is_enemy_of(piece); }
	const e_squares_type& get_eligible_squares() const noexcept { return this->eligible_squares_; }
	void set_eligible_square(const int8_t i, Square& square) noexcept { this->eligible_squares_[i] = &square; }
	Square*& get_eligible_square(const int8_t i) noexcept { return this->eligible_squares_[i]; }
	void set_pinning_filter(const pinning_filter_type func) { this->pinning_filter_ = func; }
	void filter_eligible_squares_if_pinned() noexcept { if (this->pinning_filter_) this->pinning_filter_(*this); }
protected:
	pinning_filter_type pinning_filter_{nullptr};
	BoardGame& board_;
	Square* square_{nullptr};
	std::unique_ptr<PieceColor> color_;
	e_squares_type eligible_squares_{ nullptr };
};

class CHESS_API Rock final: public Piece
{
public:
	Rock(BoardGame& board,Square& square, std::unique_ptr<PieceColor> color): Piece(board, square, std::move(color)) {}
	void compute_eligible_squares() noexcept override;	
};


class CHESS_API Bishop final: public Piece
{
public:
	Bishop(BoardGame& board,Square& square, std::unique_ptr<PieceColor> color): Piece(board, square, std::move(color)) {}
	void compute_eligible_squares() noexcept override;	
};

class CHESS_API Queen final: public Piece
{
public:
	Queen(BoardGame& board,Square& square, std::unique_ptr<PieceColor> color): Piece(board, square, std::move(color)) {}
	void compute_eligible_squares() noexcept override;	
};

class CHESS_API King final: public Piece
{
public:
	King(BoardGame& board,Square& square, std::unique_ptr<PieceColor> color): Piece(board, square, std::move(color)) {}
	void compute_eligible_squares() noexcept override;	
};


class CHESS_API Knight final: public Piece
{
public:
	Knight(BoardGame& board,Square& square, std::unique_ptr<PieceColor> color): Piece(board, square, std::move(color)) {}
	void compute_eligible_squares() noexcept override;	
};


class CHESS_API Pawn final: public Piece
{
public:
	Pawn(BoardGame& board,Square& square, std::unique_ptr<PieceColor> color): Piece(board, square, std::move(color)) {}
	void compute_eligible_squares() noexcept override;	
};

