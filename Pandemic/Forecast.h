#pragma once

#include "Action.h"
#include "City.h"
#include "InfectionCard.h"

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
		std::vector<std::unique_ptr<InfectionCard>> _target; //this is added to separate the solicitData() and perform()
	};
}