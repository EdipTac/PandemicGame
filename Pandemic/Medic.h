#pragma once

#include "RoleCard.h"

namespace role
{
	class Medic
		: public RoleCard
	{
	public:
		Medic();
		virtual ~Medic() override;
		virtual void onEnter(City& city) const override;
		virtual void treatDisease(City& city, const Colour& colour) const override;
	};
}
