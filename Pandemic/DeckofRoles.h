#pragma once
#include <string>
#include <vector>
#include "RoleCard.h"
#include <memory>
#include "Deck.h"
using uniquerolecard = std::unique_ptr < RoleCard >;

/*
This code is for the Deck of role cards that will be used in the actual game.
The aim of this code was to create an individual deck that will contain all of the role cards, 
and have the player pick his random role card from this deck.
*/

class DeckofRoles: public Deck <RoleCard>{
public: 
	DeckofRoles(); //constructor
	uniquerolecard drawRoleCard(); //this should not be needed since the base class has the drawCard function //the act of drawing a card to retun a role card


private:
	std::vector < uniquerolecard > deckofRole; //out deck of role cards
	
};