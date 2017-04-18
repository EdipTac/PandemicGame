#include "TakeKnowledgeFromResearcher.h"
#include "Player.h"
#include "Board.h"
#include "MenuUtils.h"
#include "PlayerCityCard.h"

action::TakeKnowledgeFromResearcher::TakeKnowledgeFromResearcher(Player* const performer)
	: Action { "Take Knowledge From Researcher [Researcher Shared Ability]", "Take any card from researcher", performer }
{}

action::TakeKnowledgeFromResearcher::~TakeKnowledgeFromResearcher() {}

void action::TakeKnowledgeFromResearcher::solicitData()
{
	// Reset
	_card = nullptr;

	// Set recipient
	_recipient = &Board::instance().currentPlayer();

	// Pick a card
	const auto& cards = _performer->cityCards();
	if (cards.empty())
	{
		std::cout << "No cards to give.\n";
		return;
	}

	_card =
		namedMenu(cards)
		.setMessage("Pick a card to take: ")
		.solicitInput();
}

void action::TakeKnowledgeFromResearcher::perform()
{
	_performer->giveCard(*_card, *_recipient);
}

bool action::TakeKnowledgeFromResearcher::isValid() const
{
	return _performer && _card && _recipient;
}
