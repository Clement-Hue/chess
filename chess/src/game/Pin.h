#pragma once
#include "Piece.h"

 namespace pin
{
	CHESS_API void rank_filter(Piece& piece);
	CHESS_API void file_filter(Piece& piece);
	CHESS_API void diagonal_filter(Piece& piece);
	CHESS_API void anti_diagonal_filter(Piece& piece);
}
