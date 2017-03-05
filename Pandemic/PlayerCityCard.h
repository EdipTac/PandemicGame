#pragma once

#include "City.h"
#include "PlayerCard.h"
#include "CityCard.h"
#include <string>

// PlayerCityCard class - represents PlayerCards of type City.
class PlayerCityCard : public PlayerCard, CityCard {
public:
	// Default Constructor
	//PlayerCityCard();
	// Constructor
	PlayerCityCard(City& city);

	~PlayerCityCard() override;

	// Custom implementation of the inherited virtual function from PlayerCard
	std::string toString();
};