#include "PlayerCityCard.h"

// Default Constructor
PlayerCityCard::PlayerCityCard()
	: PlayerCard() {}

// Constructor
PlayerCityCard::PlayerCityCard(std::string name)
	: PlayerCard(name) {}

// Custom implementation of the inherited virtual function from PlayerCard
std::string PlayerCityCard::toString()
{
	return "PlayerCityCard\n" + PlayerCard::toString();
}
