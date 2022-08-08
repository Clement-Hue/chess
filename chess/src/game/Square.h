#pragma once
#include <cstdint>
#include "../Common.h"

class Piece;

class CHESS_API Square
{
public:
	explicit Square(const int8_t value, Piece* piece = nullptr): value_{value}, piece_{piece} {}
	Piece* get_piece() const noexcept { return this->piece_; }
	int8_t get_value() const noexcept { return this->value_; }
	void set_piece(Piece& piece) noexcept { this->piece_ = &piece; }
	void remove_piece() noexcept { this->piece_ = nullptr; }
	bool is_same_rank(const Square& other) const noexcept { return this->get_rank() == other.get_rank(); }
	bool is_same_rank(int8_t value) const noexcept;
	bool is_same_file(const Square& other) const noexcept { return this->get_file() == other.get_file(); }
	bool is_same_file(int8_t value) const noexcept;
	bool is_same_diagonal(const Square& square) const noexcept;
	bool is_same_diagonal(int8_t value) const noexcept;
	bool is_same_anti_diagonal(const Square& square) const noexcept;
	bool is_same_anti_diagonal(int8_t value) const noexcept;
	bool is_free() const noexcept { return this->piece_ == nullptr; }
	bool has_enemy_piece_of(const Piece& piece) const noexcept;
	bool has_friend_piece_of(const Piece& piece) const noexcept;
	int8_t get_rank() const noexcept;
	int8_t get_file() const noexcept;
	bool operator==(const Square& other) const noexcept { return other.value_ == this->value_; }
	bool operator!=(const Square& other) const noexcept { return !(other == *this); }
	bool operator<(const Square& other) const noexcept { return this->value_ < other.value_; }
	bool operator>(const Square& other) const noexcept { return this->value_ > other.value_; }
	bool operator<=(const Square& other) const noexcept { return this->value_ <= other.value_; }
	bool operator>=(const Square& other) const noexcept { return this->value_ >= other.value_; }
private:
	int8_t value_;
	Piece* piece_;
};

