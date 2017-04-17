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

	private:
		std::unique_ptr<EventCard> _storedCard;
	};
}
