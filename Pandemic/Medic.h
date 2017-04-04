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
	};
}
