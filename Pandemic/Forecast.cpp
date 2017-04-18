#include "Forecast.h"
#include "Player.h"
#include "Board.h"

action::Forecast::Forecast(Player* const performer)
	: Action{ "Forecast", "Examine the top 6 cards of the Infection Draw Pile, rearrange them in the order of your choice, then place them back on the pile", performer } {}

void action::Forecast::solicitData()
{
	// Reset
	_target.clear();

	const auto& cards = Board::instance().infectionDeck().drawPile();
	const size_t count = std::min(6ull, cards.size());
	
	if (count == 0)
	{
		std::cout << "No infection cards to draw from. \n";
		return;
	}
	// the following has been changed:
	//_target.push_back(Board::instance().infectionDeck().drawTopCard()); // changed to topCards.push_back.....


	std::vector<std::unique_ptr<InfectionCard>> topCards;
	for (size_t i = 0; i < count; ++i)
	{
		topCards.push_back(Board::instance().infectionDeck().drawTopCard());
	}
	std::cout << "The following are the " << (int)count << " top cards in the Infection Draw Pile: \n"; // added (int) to (int)count to cast it to an integer type
	size_t index = 0; //changes from int index = 0 to size_t to see if it will help
	for (auto it = topCards.begin(); it != topCards.end(); ++it, ++index)
	{
		std::cout << "Card at index:" << index << " is " << (*it)->name() <<" " << (*it)->description() << std::endl;
	}
	std::cout << "Please enter the order in which you would like to add the cards to the deck. Index 5 will be drawn first and index 0 will be drawn last. \n ";
	std::string input;
	for (index = 0; index < count; ++index)
	{
		while (true)
		{
			std::cout << "Please enter the name of card name you would like to make at index " << (count - index - 1) << ": \n";
			std::getline(std::cin >> std::ws, input);
			const auto& it = std::find_if(topCards.begin(), topCards.end(), [&](const auto& c)
			{
				return input == c->name();
			});
			if (it == topCards.end())
			{
				std::cout << "No city of that name.\n";
			}
			else
			{
				_target.push_back(std::move(*it));
				topCards.erase(it);
				break;
			}
		}
	}
}

void action::Forecast::perform() {
	for (unsigned i = 0u; i < _target.size(); ++i)
	{
		Board::instance().infectionDeck().addToDeck(std::move(_target[_target.size() - i - 1]));
	}
}

bool action::Forecast::isValid() const {
	return true;
}

