#pragma once

#include "Action.h"
#include "City.h"

namespace action
{
	class Forecast
		: public Action
	{
	public:
		Forecast(Player* const performer = nullptr);
		virtual void solicitData() override;
		virtual void perform() override;
		virtual bool isValid() const override;
	
	private:
		City* _target; //i dont need a private for this class, is there a way to not put this and still go through with it?
	};
}