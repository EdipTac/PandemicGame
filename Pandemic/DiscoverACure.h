#pragma once

#include <vector>

#include "Action.h"
#include "Colour.h"

class City;
class PlayerCityCard;

namespace action
{
	class DiscoverACure
		: public Action
	{
	public:
		DiscoverACure(Player* const performer = nullptr);
		virtual void solicitData() override;
		virtual void perform() override;
		virtual bool isValid() const override;

	private:
		Colour _colour;
		std::vector<PlayerCityCard*> _cards;
	};
}
