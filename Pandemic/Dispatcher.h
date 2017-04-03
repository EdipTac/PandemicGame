#pragma once

#include "RoleCard.h"

namespace role
{
	class Dispatcher
		: public RoleCard
	{
	public:
		Dispatcher();
		virtual ~Dispatcher() override;
	};
}
