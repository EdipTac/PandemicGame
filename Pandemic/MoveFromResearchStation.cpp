#include "MoveFromResearchStation.h"
#include "Player.h"
#include "City.h"
#include "PlayerCityCard.h"
#include "Board.h"

const std::string desc = "Move from a research station to any city by discarding any City card.";

action::MoveFromResearchStation::MoveFromResearchStation(Player* const performer)
	: Action { "Move from a research station", desc, performer }
{}

action::MoveFromResearchStation::~MoveFromResearchStation() {}

void action::MoveFromResearchStation::solicitData()
{
	if (!_performer->pawn().position().hasResearchStation())
	{
		// Can only perform this action in a city with a research station
		std::cout << "No research station in this city.\n";
		return;
	}

	// Get city cards
	const auto& cards = _performer->cityCards();
	if (cards.empty())
	{
		// Can only perform this action if you have city cards to discard
		std::cout << "No city cards in hand.\n";
		return;
	}

	// List destinations
	const auto& cities = Board::instance().map().cities();
	std::cout << "Pick a destination:\n";
	for (const auto& city : cities)
	{
		std::cout << "\t" << city->name() << "\n";
	}

	// Get destination
	std::string input;
	while (true)
	{
		std::getline(std::cin >> std::ws, input);
		const auto& it = std::find_if(cities.begin(), cities.end(), [&](const auto& c)
		{
			return input == c->name();
		});
		if (it != cities.end())
		{
			_destination = it->get();
			break;
		}
		std::cout << "No card of that name.\n";
	}

	// List city cards in hand
	std::cout << "Pick a card to discard:\n";
	for (const auto& card : cards)
	{
		std::cout << "\t" << card->name() << "\n";
	}

	// Get user input
	while (true)
	{
		std::getline(std::cin >> std::ws, input);
		const auto& it = std::find_if(cards.begin(), cards.end(), [&](const auto& c)
		{
			return input == c->name();
		});
		if (it != cards.end())
		{
			_toDiscard = *it;
			break;
		}
		std::cout << "No card of that name.\n";
	}
}

void action::MoveFromResearchStation::perform()
{
	_performer->removeCardByName(_toDiscard->name());
	_performer->pawn().setPosition(*_destination);
}

bool action::MoveFromResearchStation::isValid() const
{
	return _performer && _toDiscard && _destination;
}
