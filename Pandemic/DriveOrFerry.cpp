#include "DriveOrFerry.h"
#include "Player.h"
#include "City.h"
#include "Util.h"

using namespace action;

const std::string name = "Drive/Ferry";
const std::string description = "Move to a city connected to the one you are in.";


action::DriveOrFerry::DriveOrFerry(Player* const performer)
	: Action(name, description, performer)
{}

DriveOrFerry::~DriveOrFerry(){}

void action::DriveOrFerry::perform()
{
	// Move the action performer to the target city.
	performer->pawn().setPosition(*_target);
}

void action::DriveOrFerry::solicitData()
{
	auto& player = *performer;
	const auto& position = player.pawn().position();
	const auto& connections = position.connections();

	std::cout << "You are currently in " << position.name() << "\n";

	// Check if there are no connections - should not happen in a well-formed map
	if (connections.empty())
	{
		std::cout << "Nowhere you can drive/ferry to.\n";
		return;
	}

	// List connections
	std::cout << "You can move to\n";
	list(position.connections());

	// Get target from player and move there
	std::cout << "Where would you like to move to? ";
	std::string input;
	while (true)
	{
		std::getline(std::cin >> std::ws, input);
		const auto& cn = position.connections();
		const auto& it = std::find_if(cn.begin(), cn.end(), [&](const auto& c)
		{
			return input == c->name();
		});
		if (it != cn.end())
		{
			_target = *it;
			break;
		}
		std::cout << "No city of that name.\n";
	}
}

bool action::DriveOrFerry::isValid() const
{
	return performer && _target;
}
