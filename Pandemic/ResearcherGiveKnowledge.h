#pragma once

#include "Action.h"

class PlayerCard;

namespace action
{
	class ResearcherGiveKnowledge
		: public Action
	{
	public:
		ResearcherGiveKnowledge(Player* const performer = nullptr);
		virtual ~ResearcherGiveKnowledge() override;
		virtual void solicitData() override;
		virtual void perform() override;
		virtual bool isValid() const override;

	private:
		Player* _target;
		PlayerCard* _card;
	};
}
