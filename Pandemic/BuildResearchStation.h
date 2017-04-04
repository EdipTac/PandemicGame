#pragma once

#include "Action.h"
#include "City.h"

namespace action
{
	class BuildResearchStation
		: public Action
	{
	public:
		BuildResearchStation(Player* const performer = nullptr);
		virtual void solicitData() override;
		virtual void perform() override;
		virtual bool isValid() const override;
	private:
		City* _target;
		bool _takeFromCity;
	};

}
