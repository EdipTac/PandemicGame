#include "Airlift.h"
#include "Board.h"
#include "DirectFlight.h"

const std::string desc = "Move a pawn (your's or another player's) to any city. You must have a player's permission to move their pawn.";

action::Airlift::Airlift(Player* const performer)
	: Action{ "Airlift", desc, performer }
{}


void action::Airlift::solicitData() {
	// Reset
	_target = nullptr;

	std::cout << "Please indicate the name of the player you would like to Airlift: ";
	std::string liftee;
	std::getline(std::cin >> std::ws, liftee);
	std::cout << "\n Please indicate the city you would like to airlift to: ";
	std::string destination;
	std::getline(std::cin >> std::ws, destination);

	const auto& players = Board::instance().players();
	for (auto it = players.begin(); it != players.end(); ++it) {
		if ((*it)->name() == liftee) {
			//playerToLift = (*it); 
			_performer = (*it);
			break;
		}
	}
	

	const auto& cities = Board::instance().map().cities();
	for (auto it = cities.begin(); it != cities.end(); ++it) {
		if ((*it)->name() == destination) {
			setTarget(**it);
			break;
		}
	}



}void action::Airlift::perform() {
	//_performer->discard("Airlift", Board::instance().playerDeck()); //dont really need this anymore since pandemic.cpp takes care of the discard
	_performer->moveTo(*_target);
}

void action::Airlift::setTarget(City& target) {
	_target = &target;
	
}

bool action::Airlift::isValid() const {
	return _performer && _target;
}
