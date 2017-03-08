#include "Pawn.h"

Pawn::Pawn(const Player& owner)
	: _owner { owner }
	, _position { nullptr }
{
	// Empty
}

const Player& Pawn::owner() const
{
	return _owner;
}

City& Pawn::position()
{
	return *_position;
}

Pawn& Pawn::setPosition(City & position)
{
	_position = &position;
	return *this;
}
