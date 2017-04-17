#pragma once

#include "EventCard.h"
#include "RoleCard.h"

namespace role
{
	class ContingencyPlanner
		: public RoleCard
	{
	public:
		ContingencyPlanner();
		virtual ~ContingencyPlanner() override;
		void storeEventCard(std::unique_ptr<EventCard> card);
		bool hasStoredEventCard() const;
		EventCard& storedEventCard() const;
		void deleteStoredEventCard();

	private:
		std::unique_ptr<EventCard> _storedCard;
	};
}
