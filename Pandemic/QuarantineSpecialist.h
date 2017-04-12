#pragma once

#include "RoleCard.h"

namespace role
{
	class QuarantineSpecialist
		: public RoleCard
	{
	public:
		QuarantineSpecialist();
		virtual ~QuarantineSpecialist() override;
		virtual void onEnter(City& city) const override;
		virtual void onExit(City& city) const override;
	};
}
