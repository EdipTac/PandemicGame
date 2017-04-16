#include "GovernmentGrantCard.h"
#include <memory>


using namespace action;

GovernmentGrantCard::GovernmentGrantCard() : EventCard{ "Government Grant", "Add a Research Station to any city for free.", std::make_unique<action::GovernmentGrant>(action::GovernmentGrant()) } {}