#pragma once

#include "Action.h"

class PlayerCard;

namespace action
{
	class TakeKnowledge
		: public Action
	{
	public:
		TakeKnowledge(Player* const performer = nullptr);
		virtual void solicitData() override;
		virtual void perform() override;
		virtual bool isValid() const override;

	private:
		Player* _target;
		PlayerCard* _card;
	};
}
