#pragma once
#include "EventCard.h"
#include "Player.h"
#include "City.h"
#include "Action.h"


class City;
namespace action{




	// Represents the Airlift Event Card
	class Airlift
		: public Action
	{
	public:
		//Constructor fir Airlift event card, that sends parameters to parent
		//EventCard class
		Airlift(Player* const performer = nullptr);
		virtual void solicitData() override;
		virtual void perform() override;
		virtual bool isValid() const override;

		//std::string name() const;

		//std::string description() const;

		//virtual void performEvent(std::string liftee, std::string destination);
		//virtual void performEvent(Player* const performer, std::string destination);

		virtual void setTarget(City& target);

	private:
		City* _target;

	};
}