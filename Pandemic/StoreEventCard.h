#pragma once

#include <memory>

#include "Action.h"
#include "EventCard.h"
#include "ContingencyPlanner.h"

class City;
namespace role
{
	class ContingencyPlanner;
}

namespace action
{
	class StoreEventCard
		: public Action
	{
	public:
		StoreEventCard(Player* const performer = nullptr, role::ContingencyPlanner* const roleCard = nullptr);
		StoreEventCard(role::ContingencyPlanner* const roleCard = nullptr);
		virtual void solicitData() override;
		virtual void perform() override;
		virtual bool isValid() const override;
		void setRoleCard(role::ContingencyPlanner* const roleCard);

	private:
		role::ContingencyPlanner* _roleCard;
		std::unique_ptr<EventCard> _storedCard;
	};
}
