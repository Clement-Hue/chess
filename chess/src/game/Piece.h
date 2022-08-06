#pragma once
#include <array>
#include "Constants.h"
#include "Move.h"
#include "../Common.h"
#include "BoardIterator.h"
#include "PieceColor.h"

class Square;
class PieceColor;

class CHESS_API Piece
{
public:
	using e_moves_type = std::array<std::unique_ptr<Move>, NB_SQUARES>;
	Piece(Square* square, PieceColor& color);
	Piece(const Piece&) = delete;
	Piece(Piece&&) = delete;
	Piece& operator=(const Piece&) = delete;
	Piece& operator=(Piece&&) = delete;
	virtual ~Piece() = default;
	virtual void compute_legal_moves() noexcept = 0;
	void clear_legal_moves_except(const std::vector<int8_t>& squares_values) noexcept;
	virtual void clear_legal_moves() noexcept;
	virtual void remove_illegal_moves_of_enemy(PieceColor& enemy_color) noexcept = 0;
	bool move(Square& square) noexcept;
	void remove_square() noexcept { this->square_ = nullptr; }
	Square* get_square() const noexcept { return this->square_; }
	void set_square(Square& square) noexcept { this->square_ = &square; }
	PieceColor& get_color() const noexcept { return this->color_; }
	bool is_enemy_of(const Piece& piece) const noexcept;
	bool is_friend_of(const Piece& piece) const noexcept;
	const e_moves_type& get_legal_moves() const noexcept { return this->legal_moves_; }
	std::vector<Square*> get_squares_of_legal_moves() const noexcept;
	std::unique_ptr<Move> & get_legal_move(const int8_t i) noexcept { return this->legal_moves_[i]; }
	bool has_moved() const noexcept { return this->has_moved_; };
	bool is_in_board() const noexcept { return this->square_; }
	void mark_as_moved() noexcept { this->has_moved_ = true; }
	virtual bool is_on_start() const noexcept = 0;
protected:
	Square* square_{nullptr};
	PieceColor& color_;
	e_moves_type legal_moves_{ nullptr };
	bool has_moved_{ false };
};

class CHESS_API Rock final: public Piece
{
public:
	Rock(Square* square, PieceColor& color) : Piece(square, color) {}
	void compute_legal_moves() noexcept override;
	void remove_illegal_moves_of_enemy(PieceColor&) noexcept override;
	bool is_on_start() const noexcept override;
};


class CHESS_API Bishop final: public Piece
{
public:
	Bishop(Square* square, PieceColor& color): Piece(square, color) {}
	void compute_legal_moves() noexcept override;
	void remove_illegal_moves_of_enemy(PieceColor&) noexcept override;
	bool is_on_start() const noexcept override;
};

class CHESS_API Queen final: public Piece
{
public:
	Queen(Square* square, PieceColor& color): Piece(square, color) {}
	void compute_legal_moves() noexcept override;
	void remove_illegal_moves_of_enemy(PieceColor&) noexcept override;
	bool is_on_start() const noexcept override;
};

class CHESS_API King final: public Piece
{
public:
	King(Square* square, PieceColor& color): Piece(square, color) {}
	void compute_legal_moves() noexcept override;
	void remove_illegal_moves_of_enemy(PieceColor&) noexcept override;
	bool is_on_start() const noexcept override;
private:
	using increment_fn_type = void (*)(BoardIterator&);
	template <typename Fn>
	void legal_squares(const Fn&) noexcept;
	void add_castling_move(increment_fn_type) noexcept;
	void add_long_castle_if_possible() noexcept { this->add_castling_move([](BoardIterator& it) {--it; }); }
	void add_short_castle_if_possible() noexcept { this->add_castling_move([](BoardIterator& it) {++it; }); }
};


class CHESS_API Knight final: public Piece
{
public:
	Knight(Square* square, PieceColor& color): Piece(square, color) {}
	void compute_legal_moves() noexcept override;
	void remove_illegal_moves_of_enemy(PieceColor&) noexcept override;
	bool is_on_start() const noexcept override;
private:
	template <typename It1, typename It2, typename Fn>
	void legal_squares(const Fn&) noexcept;
};


class CHESS_API Pawn final: public Piece
{
public:
	Pawn(Square* square, PieceColor& color): Piece(square, color) {}
	void compute_legal_moves() noexcept override;
	bool is_on_start() const noexcept override;
	void add_move(const Square&) noexcept;
	void mark_as_double_moved() noexcept { this->has_double_moved_ = true; }
	bool has_double_moved() const noexcept { return this->has_double_moved_; }
	void clear_legal_moves() noexcept override;
	void remove_illegal_moves_of_enemy(PieceColor&) noexcept override;
private:
	bool has_double_moved_{ false };
};

