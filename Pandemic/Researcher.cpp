#include "Researcher.h"
#include "ResearcherGiveKnowledge.h"

const std::string desc =
	"As an action, the Researcher may give any City card from her hand to "
	"another player in the same city as her, without this card having to "
	"match her city.\nThe transfer must be from her hand to the other "
	"player’s hand, but it can occur on either player’s turn.";

role::Researcher::Researcher()
	: RoleCard { "Researcher", desc, "Brown" }
{
	_actions.push_back(std::make_unique<action::ResearcherGiveKnowledge>());
}

role::Researcher::~Researcher() {}
