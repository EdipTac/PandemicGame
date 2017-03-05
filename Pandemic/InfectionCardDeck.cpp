/*
InfectionDeckCard.cpp: .cpp source of InfectionDeckCard class and functions
Author: Ke chun Ye
Version: 1.0
Data: 20170209*/
#include <iostream>
#include "InfectionCardDeck.h"
#include <ctime>
#include <string>

using namespace std;

InfectionCardDeck::InfectionCardDeck() {
	// put 48 infection cards on deck

	/*deck.push_back(InfectionCard { "Altlanta", "Blue" });
	deck.push_back(InfectionCard("Newyork", "Blue"));
	deck.push_back(InfectionCard("Paris", "Blue"));
	deck.push_back(InfectionCard("London", "Blue"));
	deck.push_back(InfectionCard("Montreal", "Blue"));
	deck.push_back(InfectionCard("Chicago", "Blue"));
	deck.push_back(InfectionCard("San Francisco", "Blue"));
	deck.push_back(InfectionCard("Washongton", "Blue"));
	deck.push_back(InfectionCard("Madrid", "Blue"));
	deck.push_back(InfectionCard("Essen", "Blue"));
	deck.push_back(InfectionCard("St.Petersburg", "Blue"));
	deck.push_back(InfectionCard("Milan", "Blue"));
	deck.push_back(InfectionCard("Shanghai", "Red"));
	deck.push_back(InfectionCard("Tokyo", "Red"));
	deck.push_back(InfectionCard("Beijing", "Red"));
	deck.push_back(InfectionCard("Taipei", "Red"));
	deck.push_back(InfectionCard("Seoul", "Red"));
	deck.push_back(InfectionCard("Osaka", "Red"));
	deck.push_back(InfectionCard("Hongkong", "Red"));
	deck.push_back(InfectionCard("Bangkok", "Red"));
	deck.push_back(InfectionCard("Manila", "Red"));
	deck.push_back(InfectionCard("Ho Chi Minh City", "Red"));
	deck.push_back(InfectionCard("Jakarta", "Red"));
	deck.push_back(InfectionCard("Sydney", "Red"));
	deck.push_back(InfectionCard("Istanbul", "Black"));
	deck.push_back(InfectionCard("Moscow", "Black"));
	deck.push_back(InfectionCard("Delhi", "Black"));
	deck.push_back(InfectionCard("Mumbai", "Black"));
	deck.push_back(InfectionCard("Chennai", "Black"));
	deck.push_back(InfectionCard("Riyadh", "Black"));
	deck.push_back(InfectionCard("Karachi", "Black"));
	deck.push_back(InfectionCard("Kolkata", "Black"));
	deck.push_back(InfectionCard("Tehran", "Black"));
	deck.push_back(InfectionCard("Baghdad", "Black"));
	deck.push_back(InfectionCard("Algiers", "Black"));
	deck.push_back(InfectionCard("Cairo", "Black"));
	deck.push_back(InfectionCard("Lagos", "Yellow"));
	deck.push_back(InfectionCard("Lima", "Yellow"));
	deck.push_back(InfectionCard("Bogota", "Yellow"));
	deck.push_back(InfectionCard("Kinshasa", "Yellow"));
	deck.push_back(InfectionCard("Johannesburg", "Yellow"));
	deck.push_back(InfectionCard("Khartoum", "Yellow"));
	deck.push_back(InfectionCard("Sao Paulo", "Yellow"));
	deck.push_back(InfectionCard("Buenos Aires", "Yellow"));
	deck.push_back(InfectionCard("Santiago", "Yellow"));
	deck.push_back(InfectionCard("Mexico City", "Yellow"));
	deck.push_back(InfectionCard("Miami", "Yellow"));
	deck.push_back(InfectionCard("Los Angeles", "Yellow"));
	infectionRate = outbreakTracker[outbreakMarker];
    shuffle(deck);// shuffle infection cards on deck*/
}
void InfectionCardDeck::shuffle(vector <InfectionCard> & cards) {


	//srand(time(0));
	//int index;
	//InfectionCard temp;
	//for (unsigned int i = 0; i < cards.size(); i++) {
	//	index = rand() % cards.size();
	//	temp = cards[i];
	//	cards[i] = cards[index];
	//	cards[index] = temp;

	//}

}
InfectionCardDeck::~InfectionCardDeck() {

}

void InfectionCardDeck::print() {
	//for (unsigned int i = 0; i < deck.size(); i++) {
	//	cout << "Infection card: " << deck[i].getCity() <<" " <<deck[i].getColor()<<endl;
	//}
}
void InfectionCardDeck::checkInfectionCardHistory() {
	//for (unsigned int i = 0; i < discardPile.size(); i++) {
	//	cout << "Infection card: " << discardPile[i].getCity()<<" "<<discardPile[i].getColor() << endl;
	//}
}
void InfectionCardDeck::flipInfectionCard() {
	if (deck.size() < 1) {
		cout << "There is no more infection cards to draw " << endl;

	}
	else {

		InfectionCard temp = deck[deck.size() -1];
		deck.pop_back();
		deck.shrink_to_fit();
		discardPile.push_back(temp);

	}
}
int InfectionCardDeck::getInfectionRate() {
	return infectionRate;
}
void InfectionCardDeck::moveOutbreakMarker() {
	if (outbreakMarker = 5) {
		cout << "Outbreak tracker reaches the last space, the game is over. " << endl;
		system("pause");
		system(0);
	}
	outbreakMarker++;
	infectionRate = outbreakTracker[outbreakMarker];
}
void InfectionCardDeck::pullBottomInfectionCard() {
	discardPile.push_back(deck[0]);
//	deck.erase(deck.begin());
	deck.shrink_to_fit();

}
void InfectionCardDeck::reshuffleAndputback() {
	shuffle(discardPile);
	const auto k = discardPile.size();
	for (auto i = 0; i < k; i++) {
		deck.push_back(discardPile[i]);
	}
	discardPile.clear();
}
