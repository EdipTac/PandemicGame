#include "Dispatcher.h"
#include "Dispatch.h"

const std::string desc =
		"The Dispatcher may, as an action, either:\n"
		"  - move any pawn, if its owner agrees, to any city containing another pawn, or\n"
		"  - move another player's pawn, if its owner agrees,as if it were his own.\n"
		"Note: When moving a player’s pawn as if it were your own, discard cards for Direct and Charter Flights from your hand.\n"
		"A card discarded for a Charter Flight must match the city the pawn is moving from. The Dispatcher can only MOVE other \n"
		"players' pawns; he may not direct them to do other actions, such as Treat Disease.";

role::Dispatcher::Dispatcher()
	: RoleCard { "Dispatcher", desc, "Pink" }
{
	_actions.push_back(std::make_unique<action::Dispatch>());
}

role::Dispatcher::~Dispatcher() {}
