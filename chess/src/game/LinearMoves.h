#pragma once
#include "Piece.h"


namespace linear_moves
{
	void add_rank_moves(Piece& piece, BoardGame& board);
	void add_file_moves(Piece& piece, BoardGame& board);
	void add_diagonal_moves(Piece& piece, BoardGame& board);
	void add_anti_diagonal_moves(Piece& piece, BoardGame& board);

	void remove_illegal_rank_moves(Piece& piece, BoardGame& board, PieceColor& enemy_color);
	void remove_illegal_file_moves(Piece& piece, BoardGame& board, PieceColor& enemy_color);
	void remove_illegal_diagonal_moves(Piece& piece, BoardGame& board, PieceColor& enemy_color);
	void remove_illegal_anti_diagonal_moves(Piece& piece, BoardGame& board, PieceColor& enemy_color);
}

