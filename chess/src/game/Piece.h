#pragma once
#include <array>
#include "Constants.h"
#include "../Common.h"
#include "BoardIterator.h"
#include "PieceColor.h"

class Square;
class PieceColor;
class Rock;
class Bishop;
class Knight;
class Pawn;
class King;
class Queen;

class CHESS_API PieceVisitor
{
public:
	PieceVisitor() = default;
	PieceVisitor(const PieceVisitor&) = delete;
	PieceVisitor(PieceVisitor&&) = delete;
	PieceVisitor& operator=(const PieceVisitor&) = delete;
	PieceVisitor& operator=(PieceVisitor&&) = delete;
	virtual void visit(Queen& piece) const = 0;
	virtual void visit(King& piece) const = 0;
	virtual void visit(Rock& piece) const = 0;
	virtual void visit(Bishop& piece) const = 0;
	virtual void visit(Knight& piece) const = 0;
	virtual void visit(Pawn& piece) const = 0;
	virtual ~PieceVisitor() = default;
};

class CHESS_API Piece
{
public:
	using e_squares_type = std::array<Square*, NB_SQUARES>;
	using pinning_filter_type = void (*)(Piece&);
	Piece(Square* square, PieceColor& color);
	Piece(const Piece&) = delete;
	Piece(Piece&&) = delete;
	Piece& operator=(const Piece&) = delete;
	Piece& operator=(Piece&&) = delete;
	virtual ~Piece() = default;
	virtual void compute_pseudo_legal_squares() noexcept = 0;
	virtual void compute_legal_squares() noexcept;
	void clear_legal_squares_states() noexcept;
	bool move(Square& square) noexcept;
	void remove_square() noexcept { this->square_ = nullptr; }
	const Square* get_square() const noexcept { return this->square_; }
	PieceColor& get_color() const noexcept { return this->color_; }
	bool is_enemy_of(const Piece& piece) const noexcept;
	bool is_friend_of(const Piece& piece) const noexcept;
	const e_squares_type& get_legal_squares() const noexcept { return this->legal_squares_; }
	Square*& get_legal_square(const int8_t i) noexcept { return this->legal_squares_[i]; }
	void set_pinning_filter(const pinning_filter_type func) { this->pinning_filter_ = func; }
	virtual void accept(const PieceVisitor& visitor) = 0;
	bool has_moved() const noexcept { return this->has_moved_; };
	bool is_in_board() const noexcept { return this->square_; }
protected:
	void filter_legal_squares_if_pinned() noexcept { if (this->pinning_filter_) this->pinning_filter_(*this); }
	pinning_filter_type pinning_filter_{nullptr};
	Square* square_{nullptr};
	PieceColor& color_;
	e_squares_type legal_squares_{ nullptr };
	bool has_moved_{ false };
};

class CHESS_API Rock final: public Piece
{
public:
	Rock(Square* square, PieceColor& color) : Piece(square, color) {}
	void compute_pseudo_legal_squares() noexcept override;	
	void accept(const PieceVisitor& visitor) override { visitor.visit(*this); }
};


class CHESS_API Bishop final: public Piece
{
public:
	Bishop(Square* square, PieceColor& color): Piece(square, color) {}
	void compute_pseudo_legal_squares() noexcept override;	
	void accept(const PieceVisitor& visitor) override { visitor.visit(*this); }
};

class CHESS_API Queen final: public Piece
{
public:
	Queen(Square* square, PieceColor& color): Piece(square, color) {}
	void compute_pseudo_legal_squares() noexcept override;	
	void accept(const PieceVisitor& visitor) override { visitor.visit(*this); }
};

class CHESS_API King final: public Piece
{
public:
	King(Square* square, PieceColor& color): Piece(square, color) {}
	void compute_pseudo_legal_squares() noexcept override;	
	void compute_legal_squares() noexcept override;
	void accept(const PieceVisitor& visitor) override { visitor.visit(*this); }
};


class CHESS_API Knight final: public Piece
{
public:
	Knight(Square* square, PieceColor& color): Piece(square, color) {}
	void compute_pseudo_legal_squares() noexcept override;	
	void accept(const PieceVisitor& visitor) override { visitor.visit(*this); }
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
	void accept(const PieceVisitor& visitor) override { visitor.visit(*this); }
	bool is_on_start() const noexcept;
};



