#include "DeckofEvents.h"
#include <string>
#include <vector>



DeckofEvents::DeckofEvents() {
	deckofEvents.push_back(std::make_unique<EventCard>("Airlift","Move a pawn (your's or another player's) to any city. You must have a player's permission to move their pawn."));
	deckofEvents.push_back(std::make_unique<EventCard>("One Quiet Night", "The next player to begin Playing The Infector phase of their turn may skip that phase entirely."));
	deckofEvents.push_back(std::make_unique<EventCard>("Resilient Population","Take a card from the Infection Discard Pile and remove it from the game."));
	deckofEvents.push_back(std::make_unique<EventCard>("Government Grant","Add a Research Station to any city for free."));
	deckofEvents.push_back(std::make_unique<EventCard>("Forecast","Examine the top 6 cards of the Infection Draw Pile, rearrange them in the order of your choice, then place them back on the pile."));
}
