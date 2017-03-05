#pragma once
#include "PlayerCard.h"
#include "CityCard.h"
#include <string>

// PlayerCityCard class - represents PlayerCards of type City.
class PlayerCityCard : public PlayerCard, CityCard {
public:
	// Default Constructor
	PlayerCityCard();
	// Constructor
	PlayerCityCard(std::string name);

	// Custom implementation of the inherited virtual function from PlayerCard
	std::string toString();
};