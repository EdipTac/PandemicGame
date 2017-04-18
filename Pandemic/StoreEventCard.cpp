#include "StoreEventCard.h"
#include "Menu.h"
#include "Board.h"

const std::string desc = 
	"Take an Event card from anywhere in the Player Discard Pile and place it on your Role card.\n"
	"Only 1 Event card can be on his role card at a time. It does not count against his hand limit.";

action::StoreEventCard::StoreEventCard(Player* const performer, role::ContingencyPlanner* const roleCard)
	: Action { "Store Event Card [Contingency Planner Ability]", desc, performer }
	, _roleCard { roleCard }
{}

action::StoreEventCard::StoreEventCard(role::ContingencyPlanner* const roleCard)
	: StoreEventCard { nullptr, roleCard }
{}

void action::StoreEventCard::solicitData()
{
	// Construct menu of discarded event cards
	Menu<EventCard*> menu;
	menu.setMessage("Pick an event card from the discard pile:");
	for (const auto& card : Board::instance().playerDeck().discardPile())
	{
		if (card->type() != PlayerCardType::EventCard)
		{
			// Not an event card, skip
			continue;
		}
		
		// Cast
		const auto& eventCard = static_cast<EventCard*>(card);
		
		// Define lambda
		const auto& getPtr = [=]()
		{
			return eventCard;
		};
		
		// Add option
		menu.addOption({ card->name(), getPtr });
	}
	menu.addOption({ "Back", []() { return nullptr; } });

	// Solicit input
	const auto& card = menu.solicitInput();

	if (!card)
	{
		return;
	}

	// Get card from discard pile and store
	_storedCard = Board::instance().playerDeck().getFromDiscard(card);
}

void action::StoreEventCard::perform()
{
	_roleCard->storeEventCard(std::move(_storedCard));
}

bool action::StoreEventCard::isValid() const
{
	return _storedCard && _roleCard;
}
