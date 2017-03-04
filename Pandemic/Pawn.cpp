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

const City& Pawn::position() const
{
	return *_position;
}

Pawn& Pawn::setPosition(const City & position)
{
	_position = &position;
	return *this;
}
