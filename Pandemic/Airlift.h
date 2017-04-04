#pragma once
#include "EventCard.h"
#include "Player.h"
#include "City.h"


// Represents the Airlift Event Card
class Airlift
	: public EventCard
{
public:
	//Constructor fir Airlift event card, that sends parameters to parent
	//EventCard class
	Airlift();
	~Airlift();
	
	//std::string name() const;
	
	//std::string description() const;

	virtual void performEvent(std::string liftee, std::string destination);








};