#include "PawnMoves.h"

void PawnLegalMoves::visit(BlackColor& color) const
{
	this->add_legal_file_squares<BlackColor>(color);
	this->add_takeable_squares<BlackColor>(color);
	this->add_in_passing_move_if_possible<BlackColor>(color);
}

void PawnLegalMoves::visit(WhiteColor& color) const
{
	this->add_legal_file_squares<WhiteColor>(color);
	this->add_takeable_squares<WhiteColor>(color);
	this->add_in_passing_move_if_possible<WhiteColor>(color);
}

void RemoveIllegalMoves::visit(BlackColor& color) const
{
	this->remove_attacked_squares_of_king_moves<BlackColor>(color);
}

void RemoveIllegalMoves::visit(WhiteColor& color) const
{
	this->remove_attacked_squares_of_king_moves<WhiteColor>(color);
}


