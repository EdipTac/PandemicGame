#include "Board.h"
#include "GovernmentGrant.h"

const std::string desc = "Add a Research Station to any city for free";


action::GovernmentGrant::GovernmentGrant(Player* const performer)
	: Action{ "GovernmentGrant", desc, performer }
{}

void action::GovernmentGrant::solicitData() {
	// Reset
	_target = nullptr;

	std::cout << "Please indicate the name of the city you would like to add a Research Station to";;
	std::string destination;
	std::getline(std::cin >> std::ws, destination);

	const auto& cities = Board::instance().map().cityView();
	for (auto it = cities.begin(); it != cities.end(); ++it) {
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
	//_performer->discard("GovernmentGrant", Board::instance().playerDeck()); //dont need this since the pandemic.cpp takes
	_target->giveResearchStation(Board::instance());
}