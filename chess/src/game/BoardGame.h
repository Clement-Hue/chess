#pragma once
#include <vector>
#include <memory>
#include "Common.h"
#include "Piece.h"
#include "BoardIterator.h"


class CHESS_API  BoardGame
{
	using pieces_type = std::vector<std::unique_ptr<Piece>>;
	struct Pieces
	{
		pieces_type black;
		pieces_type white;
	};
public:
	BoardGame();
	BoardGame(const BoardGame&) = delete;
	BoardGame(BoardGame&&) = delete;
	BoardGame& operator=(const BoardGame&) = delete;
	BoardGame& operator=(BoardGame&&) = delete;
	Square& operator[](const uint8_t i) noexcept { return this->squares_[i]; }
	~BoardGame() = default;
	void init_game() noexcept;
	bool has_square_value(const int8_t value) const noexcept { return value >= 0 && value < squares_.size(); }
	BoardIterator& rank_it(const Square& square) { return this->rank_iterator_.begin(square); }
	BoardIterator& file_it(const Square& square) { return this->file_iterator_.begin(square); }
	BoardIterator& diagonal_it(const Square& square) { return this->diagonal_iterator_.begin(square); }
	BoardIterator& anti_diagonal_it(const Square& square) { return this->anti_diagonal_iterator_.begin(square); }
private:
	RankIterator rank_iterator_{ *this };
	FileIterator file_iterator_{ *this };
	DiagonalIterator diagonal_iterator_{ *this };
	AntiDiagonalIterator anti_diagonal_iterator_{ *this };
	std::vector<Square> squares_;
	Pieces pieces_;
	pieces_type& get_pieces(const PieceColor color) noexcept
	{
		return color == PieceColor::black ? this->pieces_.black : this->pieces_.white;
	}
	void init_valuable_pieces(PieceColor, uint8_t) noexcept;
	void init_pawns(PieceColor, uint8_t) noexcept;
};

