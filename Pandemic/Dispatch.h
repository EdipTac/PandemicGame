#pragma once

#include "Action.h"

class City;

namespace action
{
	class Dispatch
		: public Action
	{
	public:
		Dispatch(Player* const performer = nullptr);
		virtual void solicitData() override;
		virtual void perform() override;
		virtual bool isValid() const override;

	private:
		Player* _dispatchee;
		City* _destination;
	};
}
