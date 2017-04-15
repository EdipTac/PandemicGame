#include "DeckofEvents.h"
#include <string>
#include <vector>



DeckOfEvents::DeckOfEvents() {
	_deckOfEvents.push_back(std::make_unique<EventCard>("Airlift","Move a pawn (your's or another player's) to any city. You must have a player's permission to move their pawn."));
	_deckOfEvents.push_back(std::make_unique<EventCard>("One Quiet Night", "The next player to begin Playing The Infector phase of their turn may skip that phase entirely."));
	_deckOfEvents.push_back(std::make_unique<EventCard>("Resilient Population","Take a card from the Infection Discard Pile and remove it from the game."));
	_deckOfEvents.push_back(std::make_unique<EventCard>("Government Grant","Add a Research Station to any city for free."));
	_deckOfEvents.push_back(std::make_unique<EventCard>("Forecast","Examine the top 6 cards of the Infection Draw Pile, rearrange them in the order of your choice, then place them back on the pile."));
}

std::vector<std::unique_ptr<EventCard>> DeckOfEvents::deckOfEvents()
{
	return std::move(_deckOfEvents);
}
