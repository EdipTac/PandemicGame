#include "OneQuietNight.h"
#include "Board.h"
#include "Player.h"

action::OneQuietNight::OneQuietNight(Player* const perfomer)
	: Action{ "One Quiet Night", "The next player to begin the Playing The Infector phase of their turn may skip that phase entirely", perfomer } {}

void action::OneQuietNight::solicitData()
{
	// Reset
	_target = nullptr;

	const auto& players = Board::instance().players();
	std::string name;
	std::cout << "Please enter the name of the player that you would like to activate One Quiet Night for. \n";

	while (true)
	{
		std::getline(std::cin >> std::ws, name);
		const auto& it = std::find_if(players.begin(), players.end(), [&](const auto& c)
		{
			return name == c->name();
		});
		if (it != players.end())
		{
			_target = (*it);
			break;
		}
		std::cout << "No player with that name.\n";
	}
}

void action::OneQuietNight::perform()
{
	bool isIt = true;
	_target->setOneQuietNight(isIt);
}

bool action::OneQuietNight::isValid() const
{
	return (true && _target);
}
