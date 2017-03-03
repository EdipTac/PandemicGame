//Header of InfectionCardDeck class
//InfectionCardDeck class represents infection card deck and discard infection card pile
//Author: Ke chun Ye
//Version: 1.0
//Data : 20170209
#ifndef	INFECTIONCARDDCEK_H
#define INFECTIONCARDDECK_H

#include <iostream>
#include <vector>
#include "InfectionCard.h"
using namespace std;

class InfectionCardDeck {
public:
	//Default constructor
	InfectionCardDeck();
	void shuffle(vector <InfectionCard> &);
	     //shuffle - shuffle infection cards in random order
	     //@param vector <InfectionCard> - infection card vector which 
	void flipInfectionCard();
	     //flipInfectionCard - flip the infection card on the top of the infection deck and put it 
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
	void setInfectionRate(int);
	     //setInfectionRate 
	     //@param int - infection rate
	void checkInfectionCardHistory();
	     //checkInfectionCardHistory - check all used infection cards
	void pullBottomInfectionCard();
	     //pullBottomInfectionCard - pull the bottom infection card on the deck
	void reshuffleAndputback();
	     //reshuffle all discard infection cards and put them back to deck
private:
	//Member variables
	int infectionRate; // infection rate
	vector <InfectionCard> deck; // vector holds all unused infection cards
	vector <InfectionCard> discardPile;// vector holds all used infection cards
	
};


#endif

