//Header of InfectionCard class
//InfectionCard class represents 48 infection cards
//Author: Ke chun Ye
//Version: 1.0
//Data : 20170209

#ifndef	INFECTIONCARD_H
#define INFECTIONCARD_H

#include <iostream>
#include <string>
#include "CityCard.h"
using namespace std;

class InfectionCard : CityCard {
public:
	//Default constructor
	InfectionCard();
	//Overload constructor
	InfectionCard(const City, const string);
	//Accessor
	string getColor() const;
	       //getColor 
	       //@return string - city color on infection card
	//Destructor
	~InfectionCard();
	
private:
	//Member variables
	string color;// infection card color
	

};


#endif
