#include "PlayerCityCard.h"

// Default Constructor
//PlayerCityCard::PlayerCityCard()
//	: PlayerCard() {}

// Constructor
PlayerCityCard::PlayerCityCard(City& city)
	: CityCard { city }
{}

PlayerCityCard::~PlayerCityCard() {}

// Custom implementation of the inherited virtual function from PlayerCard
std::string PlayerCityCard::toString()
{
	return "PlayerCityCard\n" + PlayerCard::toString();
}
