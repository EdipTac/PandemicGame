#pragma once

#include "Card.h"

// Represents a card with a custom name and description
class TextualCard
	: virtual public Card
{
public:
	// Constructs a card with a given name and description
	TextualCard(std::string name, std::string description);

	// Virutal destructor to make class abstract
	virtual ~TextualCard() override = 0;

	// The card's name
	virtual std::string name() const override;
	void setName(const std::string& name);

	// The card's description
	virtual std::string description() const override;
	void setDescription(const std::string& description);

private:
	std::string _description;
	std::string _name;
};
