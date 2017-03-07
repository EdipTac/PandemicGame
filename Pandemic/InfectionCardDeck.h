//Header of InfectionCardDeck class
//InfectionCardDeck class represents infection card deck and discard infection card pile
//Author: Ke chun Ye
//Version: 1.0
//Data : 20170209

#pragma once

#include <iostream>
#include <vector>
#include "InfectionCard.h"
#include "Serialization.h"

class InfectionCardDeck {
public:
	//Default constructor
	InfectionCardDeck(std::string fileName);
	void shuffle(std::vector <InfectionCard>& );
	     //shuffle - shuffle infection cards in random order
	     //@param vector <InfectionCard> - infection card vector which 
	void flipInfectionCard(CubePool&);
	     //flipInfectionCard - flip the infection card on the top of the infection deck and infect one specific city then put it 
	     //to the infection card discard pile
	void print();
	     //print - print all infection cards on deck. 
	     //This is a programming test method and can not be used by player.
	//Distructor
	~InfectionCardDeck();
	//Accessor
	int getInfectionRate();
		//getInfectionRate 
		//@return int - infection rate
	//Mutator function
	void moveOutbreakMarker();
	     //move outbreak marker by one 
	void checkInfectionCardHistory();
	     //checkInfectionCardHistory - check all used infection cards
	void pullBottomInfectionCard(CubePool&);
	     //pullBottomInfectionCard - When player draw the epidemic card he/she must pull one infection card from the bottom of the deck and 
	     // place three cubes on the specific city
	void reshuffleAndputback();
	     //reshuffle all discard infection cards and put them back to deck
	
private:
	//Member variables
	int infectionRate; // infection rate
	const unsigned int outbreakTracker[7] = { 2,2,2,3,3,4,4 };// outbreak marker tracker
	int outbreakMarker = 0;
	// Should be pointer
	std::vector <InfectionCard> deck; // vector holds all unused infection cards
	std::vector <InfectionCard> discardPile;// vector holds all used infection cards
	unsigned int const CUBE_NORMAL_INFECTION = 1;
	unsigned int const CUBE_EPIDEMIC_INFECTION = 3;
	
};
