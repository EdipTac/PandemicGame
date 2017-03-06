//Header of InfectionCard class
//InfectionCard class represents 48 infection cards
//Author: Ke chun Ye
//Version: 1.0
//Data : 20170209

#pragma once

#include "CityCard.h"

class InfectionCard
	: CityCard
{
public:
	InfectionCard(City& city);
	string getCityName() const; 
	Colour getCityColour() const;
	City getCity() const;
};
