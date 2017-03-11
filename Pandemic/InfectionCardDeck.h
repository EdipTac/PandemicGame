//Header of InfectionCardDeck class
//InfectionCardDeck class represents infection card deck and discard infection card pile
//Author: Ke chun Ye
//Version: 1.0
//Data : 20170209

#pragma once

#include <iostream>
#include <vector>
#include "Deck.h"
#include "InfectionCard.h"
#include "Serialization.h"

class InfectionCardDeck  : public Deck {
public:
	//Default constructor
	InfectionCardDeck(std::string fileName);
	//void shuffle(std::vector <std::unique_ptr<InfectionCard>>&);
	     //shuffle - shuffle infection cards in random order
	     //@param vector <InfectionCard> - infection card vector which 
	void printDeck();
	     //print - print all infection cards on deck. 
	     //This is a programming test method and can not be used by player.
	//Distructor
	~InfectionCardDeck();
	//Accessor
	void checkInfectionCardHistory();
	     //checkInfectionCardHistory - check all used infection cards
	void reshuffleAndputback();
	     //reshuffle all discard infection cards and put them back to deck
	

	
};
