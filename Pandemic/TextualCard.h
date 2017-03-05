#pragma once

#include "Card.h"

class TextualCard
	: virtual public Card
{
public:
	TextualCard(std::string name, std::string description);
	virtual ~TextualCard() = 0;
	virtual std::string name() const override;
	virtual std::string description() const override;
	void setName(const std::string& name);
	void setDescription(const std::string& description);

private:
	std::string _description;
	std::string _name;
};
