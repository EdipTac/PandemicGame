#include "Airlift.h"
#include "Board.h"

Airlift::Airlift()
	: EventCard{ "Airlift","Move a pawn (your's or another player's) to any city. You must have a player's permission to move their pawn." }
{}

Airlift::~Airlift() {}

void Airlift::performEvent(std::string liftee, std::string destination) {
	Player* playerToLift;
	for (auto it = Board::instance().players().begin(); it != Board::instance().players().end(); ++it) {
		if ((*it)->name() == liftee) {
			playerToLift = (*it); 
		}
	}

	//auto& position = liftee.pawn().position();
	//auto& cities = Board::instance().map().cities();
	
	for (auto it = Board::instance().map().cities().begin(); it != Board::instance().map().cities().end(); ++it) {
		if ((*it)->name() == destination) {
//			playerToLift->pawn().setPosition((**it));
		}
	}
}