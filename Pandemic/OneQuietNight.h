#pragma once

#include "Action.h"
#include "City.h"

namespace action
{
	class OneQuietNight
		: public Action
	{
	public:
		OneQuietNight(Player* const performer = nullptr);
		virtual void solicitData() override;
		virtual void perform() override;
		virtual bool isValid() const override;
	private:
		Player* _target;
	};
}