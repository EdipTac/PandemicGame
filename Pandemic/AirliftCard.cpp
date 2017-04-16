#include "AirliftCard.h"

#include <memory>

using namespace action;


AirliftCard::AirliftCard() : EventCard{ "Airlift", "Move a pawn (your's or another player's) to any city. You must have a player's permission to move their pawn.", std::make_unique<action::Airlift>(action::Airlift ())} {
}