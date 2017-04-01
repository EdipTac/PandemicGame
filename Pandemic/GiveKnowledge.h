#pragma once

#include "Action.h"

class PlayerCard;

namespace action
{
	class GiveKnowledge
		: public Action
	{
	public:
		GiveKnowledge(Player* const performer = nullptr);
		virtual void solicitData() override;
		virtual void perform() override;
		virtual bool isValid() const override;

	private:
		Player* _target;
		PlayerCard* _card;
	};
}
