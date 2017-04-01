#pragma once

#include "Action.h"

namespace action
{
	class ShareKnowledge
		: public Action
	{
	public:
		ShareKnowledge(Player* const performer = nullptr);
		virtual void solicitData() override;
		virtual void perform() override;
		virtual bool isValid() const override;
	};
}
