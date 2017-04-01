#include "ShareKnowledge.h"

const std::string desc = "You can do this action in two ways: \n GIVE the city card that matches the city you are in to another "
						 "player, or TAKE a city card that matches the city you are in from another player. The other player "
						 "must also be in the city with you. Both of you need to agree to do this. if the player who gets the card "
						 "now has more than 7 cards, that player must immediately discard a card or play an Event card.";

action::ShareKnowledge::ShareKnowledge(Player* const performer)
	: Action { "Share Knowledge", desc, performer }
{}

void action::ShareKnowledge::solicitData()
{}

void action::ShareKnowledge::perform()
{}

bool action::ShareKnowledge::isValid() const
{
	return false;
}
