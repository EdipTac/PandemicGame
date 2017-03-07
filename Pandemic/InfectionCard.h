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
	InfectionCard(City& city);
};
