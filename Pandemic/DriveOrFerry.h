#pragma once

#include "Action.h"

class City;

namespace action
{
	class DriveOrFerry :
		public Action
	{
	public:
		DriveOrFerry(Player* const performer = nullptr);
		virtual ~DriveOrFerry();
		virtual void perform() override;
		virtual void solicitData() override;
		virtual bool isValid() const override;

	private:
		City* _target;
	};
}
