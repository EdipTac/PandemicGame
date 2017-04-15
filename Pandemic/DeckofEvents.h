#pragma once
#include "Deck.h"
#include "EventCard.h"
#include <vector>


class DeckOfEvents {
public:
	DeckOfEvents();
	
	std::vector<std::unique_ptr<EventCard>> deckOfEvents();
private:
	std::vector<std::unique_ptr<EventCard>> _deckOfEvents;
};

