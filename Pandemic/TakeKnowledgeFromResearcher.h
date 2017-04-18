#pragma once

#include "Action.h"

class Player;
class PlayerCard;

namespace action
{
	class TakeKnowledgeFromResearcher
		: public Action
	{
	public:
		TakeKnowledgeFromResearcher(Player* const performer = nullptr);
		virtual ~TakeKnowledgeFromResearcher() override;
		virtual void solicitData() override;
		virtual void perform() override;
		virtual bool isValid() const override;

	private:
		PlayerCard* _card;
		Player* _recipient;
	};
}
