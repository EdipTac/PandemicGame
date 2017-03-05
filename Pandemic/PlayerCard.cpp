#include "PlayerCard.h"

// Default Constructor
//PlayerCard::PlayerCard()
//	: _name("") {}

// Constructor
PlayerCard::PlayerCard()
{}

// virtual function that converts a PlayerCard object into an informative string.
std::string PlayerCard::toString()
{
	return "Name: " + name();
}