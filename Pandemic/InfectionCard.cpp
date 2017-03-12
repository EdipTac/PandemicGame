/*
InfectionCard.cpp: .cpp source of InfectionCard class and functions
Author: Ke chun Ye
Version: 1.0
Data: 20170209*/

#include <iostream>
#include <string>

#include "City.h"
#include "InfectionCard.h"

InfectionCard::InfectionCard(City& city)
	: CityCard { city }
{} // Empty

InfectionCard::~InfectionCard(){}

void InfectionCard::onDraw(GameState& state)
{
	city().addDiseaseCubes(colour(), CUBE_NORMAL_INFECTION, state);
	std::cout << city().name() << " infected with " << colourName(city().colour()) << " disease!\n";
}
std::string InfectionCard::description() const
{
	return "This card infects " + name() + " with the " + colourAbbreviation(colour()) + " disease.";
}

void InfectionCard::cardWork(GameState& state)
{
	onDraw(state);
}