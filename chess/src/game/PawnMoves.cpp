#include "PawnMoves.h"

void PawnLegalMoves::visit(BlackColor& color) const
{
	this->add_legal_file_squares(color);
	this->add_takeable_squares(color);
	this->add_in_passing_move_if_possible(color);
}

void PawnLegalMoves::visit(WhiteColor& color) const
{
	this->add_legal_file_squares(color);
	this->add_takeable_squares(color);
	this->add_in_passing_move_if_possible(color);
}

void RemoveIllegalMoves::visit(BlackColor& color) const
{
	this->remove_illegal_moves(color);
}

void RemoveIllegalMoves::visit(WhiteColor& color) const
{
	this->remove_illegal_moves(color);
}


