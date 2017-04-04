#pragma once

#include "Action.h"

class City;
class Player;
class PlayerCard;

namespace action
{
	class MoveFromResearchStation
		: public Action
	{
	public:
		MoveFromResearchStation(Player* const performer = nullptr);
		virtual ~MoveFromResearchStation() override;
		virtual void solicitData() override;
		virtual void perform() override;
		virtual bool isValid() const override;

	private:
		City* _destination;
		PlayerCard* _toDiscard;
	};
}
