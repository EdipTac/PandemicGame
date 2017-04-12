#pragma once

#include "RoleCard.h"

namespace role
{
	class Scientist
		: public RoleCard
	{
	public:
		Scientist();
		virtual ~Scientist() override;

		int numCardsNeededToCure() const override;
	};
}
