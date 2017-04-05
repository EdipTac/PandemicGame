#include <vector>

#include "DiscoverACure.h"
#include "Player.h"
#include "City.h"
#include "PlayerCityCard.h"
#include "Board.h"

constexpr auto desc = "At ANY research station, discard 5 city cards of the same color from your hand to cure the disease of that"
						" colour. Move the disease's cure marker to its cure indicator. If no cubes of this color are on the board,"
						" this disease is now ERADICATED. Flip its cure marker from its VIAL side to its ERADICATED side.";

action::DiscoverACure::DiscoverACure(Player* const performer)
	: Action { "Discover A Cure", desc, performer }
{}

void action::DiscoverACure::solicitData()
{
	if (!_performer->pawn().position().hasResearchStation())
	{
		std::cout << "No research station in this city.\n";
		return;
	}

	const auto& cards = _performer->cityCards();
	std::map<Colour, std::vector<PlayerCityCard*>> colourCount;
	for (const auto& colour : colours())
	{
		colourCount[colour];
	}

	for (const auto& card : cards)
	{
		const auto& colour = card->colour();
		auto& cardsOfColour = colourCount[colour];
		cardsOfColour.push_back(card);
		if (cardsOfColour.size() >= 5)
		{
			_colour = colour;
			_cards = cardsOfColour;
			return;
		}
	}

	std::cout << "Not enough cards of a single colour!\n";
}

void action::DiscoverACure::perform()
{
	for (const auto& card : _cards)
	{
		_performer->discard(*card, Board::instance().playerDeck());
	}
	Board::instance().cureDisease(_colour);
}

bool action::DiscoverACure::isValid() const
{
	return _cards.size() >= 5;
}
