#pragma once

class Piece;

 namespace pin
{
	void rank_filter(Piece& piece);
	void file_filter(Piece& piece);
	void diagonal_filter(Piece& piece);
	void anti_diagonal_filter(Piece& piece);
}
