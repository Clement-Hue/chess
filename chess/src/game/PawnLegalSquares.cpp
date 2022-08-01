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
}

void PawnLegalSquares::visit(WhiteColor& color) const
{
	this->add_file_legal_squares<WhiteColor>(color);
	this->remove_not_legal_takeable_squares<WhiteColor>(color);
}

