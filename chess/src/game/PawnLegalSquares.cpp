#include "PawnLegalSquares.h"

void PawnPseudoLegalSquares::visit(BlackColor& color) const
{
	this->add_takeable_squares<BlackColor>(color);
}

void PawnPseudoLegalSquares::visit(WhiteColor& color) const
{
	this->add_takeable_squares<WhiteColor>(color);
}

void PawnLegalSquares::visit(BlackColor& color) const
{
	this->add_file_legal_squares<BlackColor>(color);
	this->remove_not_legal_takeable_squares<BlackColor>(color);
	this->add_in_passing_move_if_possible<BlackColor>(color);
}

void PawnLegalSquares::visit(WhiteColor& color) const
{
	this->add_file_legal_squares<WhiteColor>(color);
	this->remove_not_legal_takeable_squares<WhiteColor>(color);
	this->add_in_passing_move_if_possible<WhiteColor>(color);
}

