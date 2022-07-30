#pragma once
#include "Piece.h"


namespace linear_pseudo_legal_squares
{
	void add_rank_squares(Piece& piece, BoardGame& board);
	void add_file_squares(Piece& piece, BoardGame& board);
	void add_diagonal_squares(Piece& piece, BoardGame& board);
	void add_anti_diagonal_squares(Piece& piece, BoardGame& board);
}

