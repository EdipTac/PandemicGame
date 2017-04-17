#include "DriveOrFerry.h"
#include "Player.h"
#include "City.h"
#include "Util.h"
#include "MenuUtils.h"

using namespace action;

const std::string name = "Drive/Ferry";
const std::string desc = "Move to a city connected to the one you are in.";


action::DriveOrFerry::DriveOrFerry(Player* const performer)
	: Action("Drive/Ferry", desc, performer)
{}

DriveOrFerry::~DriveOrFerry(){}

void action::DriveOrFerry::perform()
{
	// Move the action performer to the target city.
	_performer->moveTo(*_target);
}

void action::DriveOrFerry::solicitData()
{
	// Reset
	_target = nullptr;


	// Aliases
	auto& player = *_performer;
	const auto& position = player.pawn().position();
	const auto& connections = position.connections();

	std::cout << "You are currently in " << position.name() << "\n";

	// Check if there are no connections - should not happen in a well-formed map
	if (connections.empty())
	{
		std::cout << "Nowhere you can drive/ferry to.\n";
		return;
	}

	// Get target from player and move there
	_target =
		namedMenu(connections)
		.setMessage("Where would you like to move to? ")
		.solicitInput();
}

bool action::DriveOrFerry::isValid() const
{
	return _performer && _target;
}
