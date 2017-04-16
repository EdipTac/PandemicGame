#include "OneQuietNightCard.h"
#include <memory>

using namespace action;

OneQuietNightCard::OneQuietNightCard() : EventCard{ "One Quiet Night", "The next player to begin the Playing The Infector phase of their turn may skip that phase entirely.", std::make_unique<action::OneQuietNight>(action::OneQuietNight()) } {}