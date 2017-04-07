#pragma once

#include <string>
#include <vector>
#include <memory>

#include "Action.h"
#include "Card.h"
#include "Colour.h"
#include "TextualCard.h"

class City;

class RoleCard
	: public TextualCard
{
public:
	RoleCard(const std::string& role = "", const std::string& description = "", const std::string& color = "");
	virtual ~RoleCard() override = 0;
	void printRole();
	void onDraw(Board& state) override;
	std::vector<action::Action*> actions() const;
	virtual int numCardsNeededToCure() const;
	virtual void onEnter(City& city) const;
	virtual void onExit(City& city) const;
	virtual void treatDisease(City& city, const Colour& colour) const;

protected:
	std::vector<std::unique_ptr<action::Action>> _actions;

private:
	std::string _color;
};
