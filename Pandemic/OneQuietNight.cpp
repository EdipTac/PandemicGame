#include "OneQuietNight.h"
#include "Board.h"
#include "Player.h"
#include "MenuUtils.h"

action::OneQuietNight::OneQuietNight(Player* const perfomer)
	: Action{ "One Quiet Night", "The next player to begin the Playing The Infector phase of their turn may skip that phase entirely", perfomer } {}

void action::OneQuietNight::solicitData()
{
	const auto& players = Board::instance().players();
	_target =
		namedMenu(players)
		.setMessage("Please enter the name of the player that you would like to activate One Quiet Night for: ")
		.solicitInput();
}

void action::OneQuietNight::perform()
{
	_target->setOneQuietNight(true);
}

bool action::OneQuietNight::isValid() const
{
	return _target;
}
