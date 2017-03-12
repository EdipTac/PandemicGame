#pragma once
#include "Deck.h"
#include "EventCard.h"
#include <vector>


class DeckofEvents {
public:
	DeckofEvents();
	
	std::vector<std::unique_ptr<EventCard>> deckOfEvents();
private:
	std::vector<std::unique_ptr<EventCard>> _deckOfEvents;
};

