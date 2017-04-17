#pragma once

#include <string>
#include <memory>
#include "PlayerCard.h"
#include "TextualCard.h"
#include "Action.h"

using namespace action;

	// Represents an Event player card
	class EventCard
		: public TextualCard
		, public PlayerCard
	{
	public:
		//template <typename T>
		// Constructs an event card with a given name and description
		EventCard(const std::string& name, const std::string& description , std::unique_ptr<Action> actions);

		// Destructor
		virtual ~EventCard() override;

		// The name of the event card
		std::string name() const override;

		// The description of the event card
		std::string description() const override;

		// Custom implementation of the inherited virtual function from PlayerCard
		virtual std::string string(const size_t spacing = 0) const override;
		virtual std::string rawString() const override;

		// Inherited via TextualCard
		virtual void onDraw() override;

		// True
		virtual bool isEventCard() const override;

		virtual Action& ability();

		virtual void cardWork(Deck<InfectionCard>& deck) override;

		virtual PlayerCardType type() const override;

	private:
		std::unique_ptr<Action> _ability;
	};
