#pragma once

#include "Action.h"

class City;
class PlayerCard;

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
		PlayerCard* _positionCard;
	};

}
