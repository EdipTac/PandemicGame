#pragma once

#include "Action.h"

class City;

namespace action
{
	class DirectFlight
		: public Action
	{
	public:
		DirectFlight(Player* const performer = nullptr);
		virtual void solicitData() override;
		virtual void perform() override;
		virtual bool isValid() const override;
		void setTarget(City* newTarget);

	private:
		City* _target;
	};
}
