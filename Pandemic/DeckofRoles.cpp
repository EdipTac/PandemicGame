#include <string>
#include <vector>
#include <memory>
#include <cstdlib>
#include <ctime>

#include "Dispatcher.h"
#include "ContingencyPlanner.h"
#include "OperationsExpert.h"
#include "RoleCard.h"
#include "DeckofRoles.h"
#include "Researcher.h"
#include "Medic.h"

/*
This is the cpp file for the deck of role cards.  It contains the constructor as well as the display method 
to indicate the role of the player along with their "abilities".
The CONSTRUCTOR is a vector of RoleCards where each card has the name, the description of the abilities
for that character,  as well as the color associated with the pawn of that role.
The "drawRoleCard" is a method that iterates through the vector of rolecards and 
picks a random role card from the deck.
*/

DeckofRoles::DeckofRoles() {
	
	deckofRole.push_back(std::make_unique<role::ContingencyPlanner>());
	deckofRole.push_back(std::make_unique<role::Dispatcher>());
	deckofRole.push_back(std::make_unique<role::Medic>());
	deckofRole.push_back(std::make_unique<role::OperationsExpert>());
	deckofRole.push_back(std::make_unique<RoleCard>("QUARANTINE SPECIALIST", "The Quarantine Specialist prevents both outbreaks and "
		"the placement of disease cubes in the city she is in "
		"and all cities connected to that city.\nShe does not affect"
		"cubes placed during setup.", "Dark Green Colored Pawn"));
	deckofRole.push_back(std::make_unique<role::Researcher>());
	deckofRole.push_back(std::make_unique<RoleCard>("SCIENTIST","The Scientist needs only 4 (not 5) City cards of "
		"the same disease color to Discover a Cure for that "
		"disease.", "White Colored Pawn"));
}
//this method draws and returns a randomly selected role card for the player
uniquerolecard DeckofRoles::drawRoleCard(){

	srand((unsigned)time(0));
	int i;
	i = (rand() % deckofRole.size());
	auto temp = move (*(deckofRole.begin()+i));
	deckofRole.erase(deckofRole.begin()+i);
	return (move(temp));
}

std::vector<std::unique_ptr<RoleCard>> DeckofRoles::roleCards()
{
	return std::move(deckofRole);
}

