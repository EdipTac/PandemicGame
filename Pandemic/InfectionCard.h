//Header of InfectionCard class
//InfectionCard class represents 48 infection cards
//Author: Ke chun Ye
//Version: 1.0
//Data : 20170209

#ifndef	INFECTIONCARD_H
#define INFECTIONCARD_H

#include <iostream>
#include <string>
using namespace std;

class InfectionCard {
public:
	//Default constructor
	InfectionCard();
	//Overload constructor
	InfectionCard(const string, const string);
	//Accessor
	string getCity() const;
	       //getCity 
	       //@return string - city name on infection card
	string getColor() const;
	       //getColor 
	       //@return string - city color on infection card
	//Destructor
	~InfectionCard();
	
private:
	//Member variables
	string name; // city name
	string color;// infection card color
	

};


#endif
