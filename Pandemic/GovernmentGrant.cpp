#include "Board.h"
#include "GovernmentGrant.h"

const std::string desc = "Add a Research Station to any city for free";


action::GovernmentGrant::GovernmentGrant(Player* const performer)
	: Action{ "GovernmentGrant", desc, performer }
{}

void action::GovernmentGrant::solicitData() {
	auto& player = *_performer;
	std::cout << "Please indicate the name of the city you would like to add a Research Station to";;
	std::string destination;
	std::getline(std::cin >> std::ws, destination);

	for (auto it = Board::instance().map().cities().begin(); it != Board::instance().map().cities().end(); ++it) {
		if ((*it)->name() == destination) {
			setTarget(**it);
		}
	}

}
void action::GovernmentGrant::setTarget(City& target) {
	_target = &target;

}

bool action::GovernmentGrant::isValid() const {
	return _performer && _target;
}

void action::GovernmentGrant::perform() {
	_performer->removeCardByName("GovernmentCard");
	_target->giveResearchStation(Board::instance());
}