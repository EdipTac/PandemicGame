/*
InfectionCard.cpp: .cpp source of InfectionCard class and functions
Author: Ke chun Ye
Version: 1.0
Data: 20170209*/

#include <iostream>
#include "InfectionCard.h"
#include <string>
using namespace std;

InfectionCard::InfectionCard() {

}
InfectionCard::~InfectionCard() {

}
InfectionCard::InfectionCard(const City n, const string c) {
	CityCard(n);
	color = c;
	
}

string InfectionCard::getColor() const {
	return  color ;
}
