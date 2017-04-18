#include "ResearcherGiveKnowledge.h"
#include "Player.h"
#include "Board.h"
#include "PlayerCityCard.h"
#include "MenuUtils.h"

const std::string desc =
		"Give any City card from her hand to another player in the same city as "
		"her, without this card having to match her city. The transfer must be "
		"from her hand to the other player’s hand, but it can occur on either "
		"player’s turn.";

action::ResearcherGiveKnowledge::ResearcherGiveKnowledge(Player* const performer)
	: Action { "Give Any Knowledge [Researcher Ability]", desc, performer }
{}

action::ResearcherGiveKnowledge::~ResearcherGiveKnowledge() {}

void action::ResearcherGiveKnowledge::solicitData()
{
	// Reset
	_target = nullptr;
	_card = nullptr;

	// Aliases
	const auto& position = _performer->pawn().position();
	const auto& players = Board::instance().players();

	// Pick a card
	const auto& cards = _performer->cityCards();
	if (cards.empty())
	{
		std::cout << "No cards to give.\n";
		return;
	}

	_card =
		namedMenu(cards)
		.setMessage("Pick a card to give: ")
		.solicitInput();

	// Select another player in your city
	std::vector<Player*> others;
	for (const auto& player : players)
	{
		if (player != _performer && player->pawn().position() == position)
		{
			others.push_back(player);
		}
	}

	// If there are none, you cannot give
	if (others.empty())
	{
		std::cout << "No other players in your city.\n";
		return;
	}

	// Select a player
	_target =
		namedMenu(others)
		.setMessage("Who to trade with? ")
		.solicitInput();
}

void action::ResearcherGiveKnowledge::perform()
{
	_performer->giveCard(*_card, *_target);
}

bool action::ResearcherGiveKnowledge::isValid() const
{
	return _performer && _target && _card;
}
