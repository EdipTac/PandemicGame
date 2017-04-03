#pragma once

#include "Action.h"
#include "Colour.h"

class City;

namespace action
{
	class TreatDisease
		: public Action
	{
	public:
		TreatDisease(Player* const performer = nullptr);
		virtual void solicitData() override;
		virtual void perform() override;
		virtual bool isValid() const override;

	private:
		Colour _colour;
		City* _city;
	};
}
