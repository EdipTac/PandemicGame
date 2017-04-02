
#include <string>
#include <vector>
#include "Dispatcher.h"
#include "OperationsExpert.h"
#include "RoleCard.h"
#include "DeckofRoles.h"
#include <memory>
#include <cstdlib>
#include <ctime>

/*
This is the cpp file for the deck of role cards.  It contains the constructor as well as the display method 
to indicate the role of the player along with their "abilities".
The CONSTRUCTOR is a vector of RoleCards where each card has the name, the description of the abilities
for that character,  as well as the color associated with the pawn of that role.
The "drawRoleCard" is a method that iterates through the vector of rolecards and 
picks a random role card from the deck.
*/

DeckofRoles::DeckofRoles() {
	
	deckofRole.push_back(std::make_unique<RoleCard>("CONTINGENCY PLANNER", "The Contingency Planner may, as an action, take an"
			"Event card from anywhere in the Player Discard Pile \n"
			"and place it on his Role card.Only 1 Event card can be"
			"on his role card at a time.It does not count against his"
			"hand limit.\n"
			"When the Contingency Planner plays the Event card on his role card,\n"
			"remove this Event card from the game(instead of discarding it).", "Teal Colored Pawn" ));
	deckofRole.push_back(std::make_unique<role::Dispatcher>());
	deckofRole.push_back(std::make_unique<RoleCard>("MEDIC", "The Medic removes ALL cubes, not 1, of the same color"
		" when doing the Treat Disease action.\n"
		"If a disease has been cured, he automatically removes "
		"all cubes of that color from a city, simply by entering it "
		"or being there.This does not take an action.\n"
		"Note: The Medic’s automatic removal of cubes can occur on other players’ \n"
		"turns, if he is moved by the Dispatcher or the Airlift Event.\n"
		"The Medic also prevents placing disease cubes (and outbreaks) of CURED diseases in his location", "Orange Colored Pawn"));
	deckofRole.push_back(std::make_unique<role::OperationsExpert>());
	deckofRole.push_back(std::make_unique<RoleCard>("QUARANTINE SPECIALIST", "The Quarantine Specialist prevents both outbreaks and "
		"the placement of disease cubes in the city she is in "
		"and all cities connected to that city.\nShe does not affect"
		"cubes placed during setup.", "Dark Green Colored Pawn"));
	deckofRole.push_back(std::make_unique<RoleCard>("RESEARCHER", "As an action, the Researcher may give any City card from "
		"her hand to another player in the same city as her, without "
		"this card having to match her city.\nThe transfer must be"
		"from her hand to the other player’s hand, but it can occur "
		"on either player’s turn.", "Brown Colored Pawn"));
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

