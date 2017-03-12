//Header of InfectionCard class
//InfectionCard class represents 48 infection cards
//Author: Ke chun Ye
//Version: 1.0
//Data : 20170209

#pragma once

#include <string>

#include "CityCard.h"

// Represents an infection card
class InfectionCard
	: public CityCard
{
public:
	// Constructs an infection card for infecting a given city
	InfectionCard(City& );
	~InfectionCard();
	unsigned const CUBE_NORMAL_INFECTION = 1;
	unsigned const CUBE_EPIDEMIC_INFECTION = 3;
	void onDraw(GameState& state);
	void cardWork(GameState&);
	std::string description() const override;

};
