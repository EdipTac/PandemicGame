#pragma once

#include "Action.h"

class City;
class Player;

namespace action
{
	class ShuttleFlight
		: public Action
	{
	public:
		ShuttleFlight(Player* const performer = nullptr);
		virtual ~ShuttleFlight() override;
		virtual void solicitData() override;
		virtual void perform() override;
		virtual bool isValid() const override;

	private:
		City* _target;
	};
}
