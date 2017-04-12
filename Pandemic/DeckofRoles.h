#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Deck.h"
#include "RoleCard.h"

/*
This code is for the Deck of role cards that will be used in the actual game.
The aim of this code was to create an individual deck that will contain all of the role cards, 
and have the player pick his random role card from this deck.
*/

class DeckofRoles
	: public Deck<RoleCard>
{
public: 
	// Ctor
	DeckofRoles();
	
};