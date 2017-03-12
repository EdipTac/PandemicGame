#pragma once
#include "Deck.h"
#include "EventCard.h"
#include <vector>


class DeckofEvents {
public:
	DeckofEvents();
	

private:
	std::vector<std::unique_ptr<EventCard>> deckofEvents;
};

