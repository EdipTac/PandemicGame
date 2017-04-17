#include "EventCard.h"
#include "Util.h"

// Constructor
EventCard::EventCard(const std::string& name, const std::string& description, std::unique_ptr<Action> actions)
	: TextualCard { name, description }
	, _ability { std::move(actions) }
{
	//_ability = std::move(actions);
}

EventCard::~EventCard() {}

std::string EventCard::name() const
{
	return TextualCard::name();
}

std::string EventCard::description() const
{
	return TextualCard::description();
}

std::string EventCard::string(const size_t spacing) const
{
	return rawString() + spaces(spacing) + " [Event Card]";
}

std::string EventCard::rawString() const
{
	return name();
}

void EventCard::onDraw() {}

bool EventCard::isEventCard() const
{
	return true;
}

Action& EventCard::ability() {
	return *_ability;
}

void EventCard::cardWork(Deck<InfectionCard>&) {}

PlayerCardType EventCard::type() const
{
	return PlayerCardType::EventCard;
}
