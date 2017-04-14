#pragma once

#include "Action.h"
#include "Colour.h"

class City;

namespace action
{
	class DoNothing
		: public Action
	{
	public:
		DoNothing(Player* const performer = nullptr);
		virtual void solicitData() override;
		virtual void perform() override;
		virtual bool isValid() const override;
		virtual void spendActionPoints(ActionController& ac) const override;
	};
}
