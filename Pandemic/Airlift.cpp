#include "Airlift.h"
#include "Board.h"
#include "DirectFlight.h"

const std::string desc = "Move a pawn (your's or another player's) to any city. You must have a player's permission to move their pawn.";

action::Airlift::Airlift(Player* const performer)
	: Action{ "Airlift", desc, performer }
{}


void action::Airlift::solicitData() {
	auto& player = *_performer;
	std::cout << "Please indicate the name of the player you would like to Airlift";
	std::string liftee;
	std::getline(std::cin >> std::ws, liftee);
	std::cout << "Please indicate the city you would like to airlift to \n";
	std::string destination;
	std::getline(std::cin >> std::ws, destination);
	Player* playerToLift = nullptr;

	for (auto it = Board::instance().players().begin(); it != Board::instance().players().end(); ++it) {
		if ((*it)->name() == liftee) {
			//playerToLift = (*it); 
			_performer = (*it);
		}
	}
	
	for (auto it = Board::instance().map().cities().begin(); it != Board::instance().map().cities().end(); ++it) {
		if ((*it)->name() == destination) {
			//_performer->pawn().setPosition((**it));
			setTarget(**it);
			//_target = (**it);
		}
	}



}void action::Airlift::perform() {
	_performer->removeCardByName("Airlift");
	_performer->pawn().setPosition(*_target);
}

void action::Airlift::setTarget(City& target) {
	_target = &target;
	
}

bool action::Airlift::isValid() const {
	return _performer && _target;
}

//void Airlift::performEvent(std::string liftee, std::string destination) {
//	Player* playerToLift=nullptr;
//	for (auto it = Board::instance().players().begin(); it != Board::instance().players().end(); ++it) {
//		if ((*it)->name() == liftee) {
//			playerToLift = (*it); 
//		}
//	}
//
//	auto& position = playerToLift->pawn().position();
//	auto& cities = Board::instance().map().cities();
//	
//	for (auto it = Board::instance().map().cities().begin(); it != Board::instance().map().cities().end(); ++it) {
//		if ((*it)->name() == destination) {
//			playerToLift->pawn().setPosition((**it));
//		}
//	}
//
//
//
//}

//void Airlift::performEvent(Player* const performer, std::string destination) {
//	action::DirectFlight obj(performer);
//	obj.setTarget()
//	//performer->
//}