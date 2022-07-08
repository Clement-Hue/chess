#pragma once
#include <cstdint>
#include "Common.h"
#include "Constants.h"

class Piece;

class CHESS_API Square
{
public:
	explicit Square(const uint8_t value, Piece* piece = nullptr): value_{value}, piece_{piece} {}
	Piece* get_piece() const noexcept { return this->piece_; }
	uint8_t get_value() const noexcept { return this->value_; }
	void set_piece(Piece& piece) noexcept { this->piece_ = &piece; }
	void remove_piece() noexcept { this->piece_ = nullptr; }
	bool is_same_rank(const Square& other) const noexcept { return this->get_rank() == other.get_rank(); }
	bool is_same_file(const Square& other) const noexcept { return this->get_file() == other.get_file(); }
	bool is_same_rank(const uint8_t row) const noexcept { return this->get_rank() == row / NB_SQUARES_BY_ROW; }
	bool is_same_file(const uint8_t column) const noexcept { return this->get_file() == column % NB_SQUARES_BY_ROW; }
	bool is_free() const noexcept { return this->piece_ == nullptr; }
	bool has_enemy_piece_of(const Piece& piece) const noexcept;
	bool has_friend_piece_of(const Piece& piece) const noexcept;
	uint8_t get_rank() const noexcept { return this->value_ / NB_SQUARES_BY_ROW; }
	uint8_t get_file() const noexcept { return this->value_ % NB_SQUARES_BY_ROW; }
	bool operator==(const Square& other) const noexcept { return other.value_ == this->value_; }
	bool operator<(const Square& other) const noexcept { return this->value_ < other.value_; }
	bool operator>(const Square& other) const noexcept { return this->value_ > other.value_; }
private:
	uint8_t value_;
	Piece* piece_;
};

