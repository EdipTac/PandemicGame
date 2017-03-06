/*
InfectionCard.cpp: .cpp source of InfectionCard class and functions
Author: Ke chun Ye
Version: 1.0
Data: 20170209*/

#include <iostream>
#include <string>

#include "InfectionCard.h"

InfectionCard::InfectionCard(City& city)
	: CityCard { city }

{}
string InfectionCard::getCityName() const{
	return name();
}
Colour InfectionCard::getCityColour() const {
	return colour();
}
City InfectionCard::getCity() const {
	return city();
}
