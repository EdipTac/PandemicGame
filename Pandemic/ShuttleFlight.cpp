#include "ShuttleFlight.h"
#include "Player.h"
#include "City.h"
#include "Board.h"

const std::string desc = "Move from a city with a research station to any other city that has a research station.";

action::ShuttleFlight::ShuttleFlight(Player* const performer)
	: Action { "Shuttle Flight", desc, performer }
{}

action::ShuttleFlight::~ShuttleFlight() {}

void action::ShuttleFlight::solicitData()
{
	// Reset
	_target = nullptr;

	// Alias
	auto& player = *_performer;

	// Not applicable if you have no research station in your city
	if (!player.pawn().position().hasResearchStation())
	{
		std::cout << "Your city does not have a research station.\n";
		return;
	}

	const auto& stations = Board::instance().map().stations(); // Alias

	// If there are no other cities with stations, you can't move anywhere
	if (stations.size() < 2)
	{
		std::cout << "There are no other cities with research stations.\n";
		return;
	}

	// List stations, get target, and move
	std::cout << "Where do you want to fly?\n";
	std::string input;
	while (true)
	{
		std::getline(std::cin >> std::ws, input);
		const auto& it = std::find_if(stations.begin(), stations.end(), [&](const auto& c)
		{
			return input == c->name();
		});
		if (it != stations.end())
		{
			_target = *it;
			break;
		}
		std::cout << "No city of that name.\n";
	}
}

void action::ShuttleFlight::perform()
{
	_performer->moveTo(*_target);
}

bool action::ShuttleFlight::isValid() const
{
	return _performer && _target;
}
