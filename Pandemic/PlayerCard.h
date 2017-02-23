#pragma once
#include <string>

// PlayerCard class - base class for all different types of PlayerCards.
class PlayerCard {
private:
	// Attributes for PlayerCard objects
	std::string _name;

public:
	// Default Constructor
	PlayerCard();
	// Constructor
	PlayerCard(std::string name);

	// Accessor and Mutators for _name
	std::string name() const;
	void setName(const std::string name);

	// virtual function that converts a PlayerCard object into an informative string.
	virtual std::string toString();
};

// PCCity class - represents PlayerCards of type City.
class PCCity : public PlayerCard {
public:
	// Default Constructor
	PCCity();
	// Constructor
	PCCity(std::string name); 

	// Custom implementation of the inherited virtual function from PlayerCard
	std::string toString();
};

// PCEvent class - represents PlayerCards of type Event.
class PCEvent : public PlayerCard {
private:
	// Attributes for PCEvent objects
	std::string _description;
public:
	// Default Constructor
	PCEvent();
	// Constructor
	PCEvent(std::string name, std::string description);

	// Accessor and Mutator for _description
	std::string description() const;
	void setDescription(const std::string description);

	// Custom implementation of the inherited virtual function from PlayerCard
	std::string toString();
};

// PCEpidemic class - represents PlayerCards of type Epidemic.
class PCEpidemic : public PlayerCard {
private:
	// Attribute for PCEpidemic objects, constant because all Epidemic cards are the same.
	const std::string EPIDEMIC_DESCRIPTION = "1-Increase:\nMove the infection rate marker forward 1 space\n2-Infect:\nDraw the bottom card from the infection deck and put 3 cubes on that city. Discard that card\n3-Intensify:\nShuffle the cards in the infection discard pile and put them on top of the infection deck.\n\n";
public:
	// Default Constructor
	PCEpidemic();

	// Accessor for EPIDEMIC_DESCRIPTION
	std::string getDescription() const;

	// Custom implementation of the inherited virtual function from PlayerCard
	std::string toString();
};