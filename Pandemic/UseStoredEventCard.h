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
	class UseStoredEventCard
		: public Action
	{
	public:
		UseStoredEventCard(Player* const performer = nullptr, role::ContingencyPlanner* const roleCard = nullptr);
		UseStoredEventCard(role::ContingencyPlanner* const roleCard = nullptr);
		virtual void solicitData() override;
		virtual void perform() override;
		virtual bool isValid() const override;

	private:
		role::ContingencyPlanner* _roleCard;
	};
}
