#include "Researcher.h"
#include "ResearcherGiveKnowledge.h"
#include "TakeKnowledgeFromResearcher.h"

const std::string desc =
	"As an action, the Researcher may give any City card from her hand to another player in the same city as her,\n"
	"without this card having to match her city. The transfer must be from her hand to the other player's hand,  \n"
	"but it can occur on either player's turn.";

role::Researcher::Researcher()
	: RoleCard { "Researcher", desc, "Brown" }
{
	_actions.push_back(std::make_unique<action::ResearcherGiveKnowledge>());
	_sharedActions.push_back(std::make_unique<action::TakeKnowledgeFromResearcher>());
}

role::Researcher::~Researcher() {}
