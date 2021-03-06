#pragma once

#include "Action.h"

class City;

namespace action
{
	class ResilientPopulation
		: public Action
	{
	public:
		ResilientPopulation(Player* const performer = nullptr);
		virtual void solicitData() override;
		virtual void perform() override;
		virtual bool isValid() const override;

	private:
		std::string _target;
	};
}