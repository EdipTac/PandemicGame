#include "Board.h"
#include "GovernmentGrant.h"

const std::string desc = "Add a Research Station to any city for free";


action::GovernmentGrant::GovernmentGrant(Player* const performer)
	: Action{ "GovernmentGrant", desc, performer }
{}

void action::GovernmentGrant::solicitData() {
	// Reset
	_target = nullptr;

	//std::cout << "Please indicate the name of the city you would like to add a Research Station to: ";
	std::string destination;
	//std::getline(std::cin >> std::ws, destination);

	const auto& cities = Board::instance().map().cities();
	while (true)
	{
		std::cout << "Please indicate the name of the city you would like to add a Research Station to: ";
		std::getline(std::cin >> std::ws, destination);
		const auto& it = std::find_if(cities.begin(), cities.end(), [&](const auto& c)
		{
			return destination == c->name();
		});
		if (it == cities.end())
		{
			std::cout << "No city of that name.\n";
			
		}
		else
		{
			setTarget(**it);
			break;
		}

	}

	/*while (looper) {
		std::cout << "Please indicate the name of the city you would like to add a Research Station to: ";
		std::getline(std::cin >> std::ws, destination);
		for (auto it = cities.begin(); it != cities.end(); ++it) {
			if ((*it)->name() == destination) {
				setTarget(**it);
				looper = false;
			}
		}
		std::cout << "No city matches that name. \n";
	}*/

}
void action::GovernmentGrant::setTarget(City& target) {
	_target = &target;

}

bool action::GovernmentGrant::isValid() const {
	//return _performer && _target;
	return true;
}

void action::GovernmentGrant::perform() {
	_target->giveResearchStation();
}