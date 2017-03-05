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

InfectionCard::~InfectionCard() {}
