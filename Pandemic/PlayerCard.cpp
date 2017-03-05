#include "PlayerCard.h"

// Default Constructor
PlayerCard::PlayerCard()
	: _name("") {}

// Constructor
PlayerCard::PlayerCard(std::string name)
	: _name(name) {}

// Accessor for _name
std::string PlayerCard::name() const
{
	return _name;
}

// Mutator for _name
void PlayerCard::setName(const std::string name)
{
	this->_name = name;
}

// virtual function that converts a PlayerCard object into an informative string.
std::string PlayerCard::toString()
{
	return "Name: " +_name;
}