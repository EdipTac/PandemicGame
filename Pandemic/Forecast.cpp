#include "Forecast.h"
#include "Player.h"
#include "Board.h"


action::Forecast::Forecast(Player * const performer)
	: Action{ "Forecast", "Examine the top 6 cards of the Infection Draw Pile, rearrange them in the order of your choice, then place them back on the pile", performer } {}

void action::Forecast::solicitData()
{
	const auto& cards = Board::instance().infectionDeck().drawPile();
	
	if (cards.empty())
	{
		std::cout << "No infection cards to draw from. \n";
	}
	std::vector<std::unique_ptr<InfectionCard>> topCards;
	for (auto it = cards.begin(); it != (cards.begin() + 6); ++it)
	{
		_target.push_back(Board::instance().infectionDeck().drawTopCard()); //this should work fine
	}
	std::cout << "The following are the 6 top cards in the Infection Draw Pile: \n";
	int index = 0;
	for (auto it = topCards.begin(); it != topCards.end(); ++it, index++)
	{
		std::cout << "Card at index:" << index << "  " << (*it)->name() <<" " << (*it)->description() << std::endl; //not sure if this *it will print out the content of the city card. Should try to make it so that it prints it->name(); just not sure how at the moment
	}
	std::cout << "Please enter the order in which you would like to add the cards to the deck \n";
	std::string input;
	index = 6;
	while (true)
	{
		std::cout << "Please enter the name of card number " << index << ". \n";
		std::getline(std::cin >> std::ws, input);
		const auto& it = std::find_if(topCards.begin(), topCards.end(), [&](const auto& c)
		{
			return input == c->name();
		});
		if (it != topCards.end())
		{
			_target.push_back(std::move(*it));
		}

		/*if (it != topCards.end())
		{
			Board::instance().infectionDeck().addToDeck(std::move(*it));
			break;
		}*/
		std::cout << "No city of that name.\n";
	}
}

void action::Forecast::perform() {
	for (unsigned i = 0u; i < _target.size(); ++i)
	{
		Board::instance().infectionDeck().addToDeck(std::move(_target[i]));
	}
}

bool action::Forecast::isValid() const {
	return (_performer!= NULL);
}

