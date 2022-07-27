#pragma once
#include <array>
#include "Constants.h"
#include "Common.h"
#include "BoardIterator.h"

class Square;
class PieceColor;

class CHESS_API Piece
{
public:
	using e_squares_type = std::array<Square*, NB_SQUARES>;
	using pinning_filter_type = void (*)(Piece&);
	virtual void compute_pseudo_legal_squares() noexcept = 0;
	void move(Square& square) noexcept;
	Piece(Square* square, PieceColor& color);
	Piece(const Piece&) = delete;
	Piece(Piece&&) = delete;
	Piece& operator=(const Piece&) = delete;
	Piece& operator=(Piece&&) = delete;
	virtual ~Piece() = default;
	void remove_square() noexcept { this->square_ = nullptr; }
	const Square* get_square() const noexcept { return this->square_; }
	PieceColor& get_color() const noexcept { return this->color_; }
	bool is_enemy_of(const Piece& piece) const noexcept;
	bool is_friend_of(const Piece& piece) const noexcept;
	const e_squares_type& get_legal_squares() const noexcept { return this->legal_squares_; }
	Square*& get_legal_square(const int8_t i) noexcept { return this->legal_squares_[i]; }
	void set_pinning_filter(const pinning_filter_type func) { this->pinning_filter_ = func; }
	virtual void compute_legal_squares() noexcept;
protected:
	void filter_legal_squares_if_pinned() noexcept { if (this->pinning_filter_) this->pinning_filter_(*this); }
	pinning_filter_type pinning_filter_{nullptr};
	Square* square_{nullptr};
	PieceColor& color_;
	e_squares_type legal_squares_{ nullptr };
};

class CHESS_API Rock final: public Piece
{
public:
	Rock(Square* square, PieceColor& color) : Piece(square, color) {}
	void compute_pseudo_legal_squares() noexcept override;	
};


class CHESS_API Bishop final: public Piece
{
public:
	Bishop(Square* square, PieceColor& color): Piece(square, color) {}
	void compute_pseudo_legal_squares() noexcept override;	
};

class CHESS_API Queen final: public Piece
{
public:
	Queen(Square* square, PieceColor& color): Piece(square, color) {}
	void compute_pseudo_legal_squares() noexcept override;	
};

class CHESS_API King final: public Piece
{
public:
	King(Square* square, PieceColor& color): Piece(square, color) {}
	void compute_pseudo_legal_squares() noexcept override;	
	void compute_legal_squares() noexcept override;
};


class CHESS_API Knight final: public Piece
{
public:
	Knight(Square* square, PieceColor& color): Piece(square, color) {}
	void compute_pseudo_legal_squares() noexcept override;	
private:
	template <typename It1, typename It2>
	void add_eligible_squares() noexcept;
};


class CHESS_API Pawn final: public Piece
{
public:
	Pawn(Square* square, PieceColor& color): Piece(square, color) {}
	void compute_pseudo_legal_squares() noexcept override;	
	void compute_legal_squares() noexcept override;
};



