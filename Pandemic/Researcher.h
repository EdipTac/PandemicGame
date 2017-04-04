#pragma once

#include "RoleCard.h"

namespace role
{
	class Researcher
		: public RoleCard
	{
	public:
		Researcher();
		virtual ~Researcher() override;
	};
}
