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

DeckOfRoles::DeckOfRoles()
{	
	_drawPile.push_back(std::make_unique<ContingencyPlanner>());
	_drawPile.push_back(std::make_unique<Dispatcher>());
	_drawPile.push_back(std::make_unique<Medic>());
	_drawPile.push_back(std::make_unique<OperationsExpert>());
	_drawPile.push_back(std::make_unique<QuarantineSpecialist>());
	_drawPile.push_back(std::make_unique<Researcher>());
	_drawPile.push_back(std::make_unique<Scientist>());
}
