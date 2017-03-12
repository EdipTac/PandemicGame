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
	std::cout << city().name() << " infected!\n";
}
std::string InfectionCard::description() const
{
    std::string descr;
	descr = "Infection card: " + name() + " with the colour of " + colourAbbreviation(colour());
	return descr;
}

void InfectionCard::cardWork(GameState& state)
{
	onDraw(state);
}