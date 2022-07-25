#pragma once
#include "Common.h"

class Piece;
class BoardGame;

namespace linear_pseudo_legal_squares
{
	CHESS_API void add_rank_squares(Piece& piece, BoardGame& board);
	CHESS_API void add_file_squares(Piece& piece, BoardGame& board);
	CHESS_API void add_diagonal_squares(Piece& piece, BoardGame& board);
	CHESS_API void add_anti_diagonal_squares(Piece& piece, BoardGame& board);
}

