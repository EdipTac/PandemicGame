#pragma once

#include "Action.h"

class City;

namespace action
{
	class CharterFlight
		: public Action
	{
	public:
		CharterFlight(Player* const performer = nullptr);
		virtual void solicitData() override;
		virtual void perform() override;
		virtual bool isValid() const override;

	private:
		City* _target;
	};
}
