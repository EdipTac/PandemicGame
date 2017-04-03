#include "ResearcherGiveKnowledge.h"
#include "Player.h"
#include "Board.h"
#include "PlayerCityCard.h"

const std::string desc =
		"Give any City card from her hand to another player in the same city as "
		"her, without this card having to match her city. The transfer must be "
		"from her hand to the other player’s hand, but it can occur on either "
		"player’s turn.";

action::ResearcherGiveKnowledge::ResearcherGiveKnowledge(Player* const performer)
	: Action { "Give Any Knowledge", desc, performer }
{}

action::ResearcherGiveKnowledge::~ResearcherGiveKnowledge() {}

void action::ResearcherGiveKnowledge::solicitData()
{
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

	std::cout << "Pick a card to give:\n";
	for (const auto& card : cards)
	{
		std::cout << "\t" << card->name() << "\n";
	}

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
			_card = *it;
			break;
		}
		std::cout << "Not a card in your hand.\n";
	}


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
	std::cout << "Who to trade with?\n";
	for (const auto& player : others)
	{
		std::cout << "\t" << player->name() << "\n";
	}
	while (true)
	{
		std::getline(std::cin >> std::ws, input);
		const auto& it = std::find_if(others.begin(), others.end(), [&](const auto& p)
		{
			return input == p->name();
		});
		if (it != others.end())
		{
			_target = *it;
			break;
		}
		std::cout << "Not a player in this city.\n";
	}
}

void action::ResearcherGiveKnowledge::perform()
{}

bool action::ResearcherGiveKnowledge::isValid() const
{
	return false;
}
