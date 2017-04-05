#pragma once

#include "Action.h"

class City;

namespace action
{
	class GovernmentGrant
		: public Action
	{
	public:
		GovernmentGrant(Player* const performer = nullptr);
		virtual void solicitData() override;
		virtual void perform() override;
		virtual bool isValid() const override;
		virtual void setTarget(City& target);
	private:
		City* _target;
	};
}