#include "DirectFlight.h"
#include "Player.h"
#include "PlayerCityCard.h"

const std::string desc = "Discard a city card to move to the city named on the card.";

action::DirectFlight::DirectFlight(Player* const performer)
	: Action { "Direct Flight", desc, performer }
{}

void action::DirectFlight::solicitData()
{
	// Aliases
	auto& player = *_performer;
	const auto& cards = player.cityCards();

	// You can't discard a card if you have none!
	if (cards.empty())
	{
		std::cout << "You have no city cards.\n";
	}

	// List cards, get player target, discard card, and move
	std::cout << "City cards: \n";
	for (const auto& card : cards)
	{
		std::cout << "\t" << card->name() << "\n";
	}
	//auto& targetCard = *validateInput(cards, "You have no city card of that name.\n");
	std::string input;
	while (true)
	{
		std::getline(std::cin >> std::ws, input);
		const auto& it = std::find_if(cards.begin(), cards.end(), [&](const auto& c)
		{
			return input == c->name();
		});
		if (it != cards.end())
		{
			_target = &(*it)->city();
			break;
		}
		std::cout << "No city of that name.\n";
	}
}

void action::DirectFlight::perform()
{
	_performer->removeCardByName(_target->name());
	_performer->pawn().setPosition(*_target);
}

bool action::DirectFlight::isValid() const
{
	return _performer && _target;
}
