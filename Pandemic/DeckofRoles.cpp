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
#include "QuarantineSpecialist.h"
#include "Scientist.h"

/*
This is the cpp file for the deck of role cards.  It contains the constructor as well as the display method 
to indicate the role of the player along with their "abilities".
The CONSTRUCTOR is a vector of RoleCards where each card has the name, the description of the abilities
for that character,  as well as the color associated with the pawn of that role.
The "drawRoleCard" is a method that iterates through the vector of rolecards and 
picks a random role card from the deck.
*/

using namespace role;

DeckofRoles::DeckofRoles()
{	
	deckOfRole.push_back(std::make_unique<ContingencyPlanner>());
	deckOfRole.push_back(std::make_unique<Dispatcher>());
	deckOfRole.push_back(std::make_unique<Medic>());
	deckOfRole.push_back(std::make_unique<OperationsExpert>());
	deckOfRole.push_back(std::make_unique<QuarantineSpecialist>());
	deckOfRole.push_back(std::make_unique<Researcher>());
	deckOfRole.push_back(std::make_unique<Scientist>());
}

//this method draws and returns a randomly selected role card for the player
uniquerolecard DeckofRoles::drawRoleCard(){

	srand((unsigned)time(0));
	int i;
	i = (rand() % deckOfRole.size());
	auto temp = move (*(deckOfRole.begin()+i));
	deckOfRole.erase(deckOfRole.begin()+i);
	return (move(temp));
}

std::vector<std::unique_ptr<RoleCard>> DeckofRoles::roleCards()
{
	return std::move(deckOfRole);
}

