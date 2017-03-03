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
InfectionCard::InfectionCard(const string n, const string c) {
	name = n;
	color = c;
	
}
string InfectionCard::getCity() const {
	return  name ;
}

string InfectionCard::getColor() const {
	return  color ;
}
