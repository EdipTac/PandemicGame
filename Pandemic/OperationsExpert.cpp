#include "OperationsExpert.h"
#include "MoveFromResearchStation.h"

const std::string desc =
	"The Operations Expert man, as an action, either\n"
	"• build a research station in his current city without "
	"discarding(or using) a City card, or\n"
	"• once per turn, move from a research station to any city "
	"by discarding any City card.\n"
	"Note: The Dispatcher may not use the Operations Expert’s special "
	"move ability when moving the Operation Expert’s pawn.";

role::OperationsExpert::OperationsExpert()
	: RoleCard { "Operations Expert", desc, "Green" }
{
	// TODO
	//_actions.push_back(std::make_unique<BuildAResearchStationFree>());
	_actions.push_back(std::make_unique<action::MoveFromResearchStation>());
}

role::OperationsExpert::~OperationsExpert() {}
