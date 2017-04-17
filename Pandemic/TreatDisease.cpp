#include <iostream>

#include "Board.h"
#include "City.h"
#include "Player.h"
#include "TreatDisease.h"
#include "MenuUtils.h"

constexpr auto desc = "Remove 1 disease cube from the city you are in, placing it in the cube suppled next to the board.";

action::TreatDisease::TreatDisease(Player* const performer)
	: Action { "Treat Disease", desc, performer }
{}

void action::TreatDisease::solicitData()
{
	// Reset
	_city = nullptr;

	auto& position = _performer->pawn().position();
	auto diseases = position.diseases();
	if (diseases.empty())
	{
		std::cout << "No disease in this city.\n";
		return;
	}

	_city = &position;

	std::vector<Colour*> dPtrs;
	for (auto& disease : diseases)
	{
		dPtrs.push_back(&disease);
	}

	// Don't have std::optional yet, need to use nullptr for "no value"... - too late to install Boost, too. Oh well
	const auto& clrPtr = makeMenu(dPtrs, [&](const auto& disease)
	{
		return colourName(*disease) + "(" + colourAbbreviation(*disease) + "): " + std::to_string(_city->diseaseCubes(*disease)) + " cubes";
	})
		.setMessage("Select a disease: ")
		.solicitInput();

	if (clrPtr)
	{
		_colour = *clrPtr;
	}
	else
	{
		_city = nullptr;
	}
}

void action::TreatDisease::perform()
{
	// Call performer's specicific treatDisease function
	_performer->role().treatDisease(*_city, _colour);

	std::cout << "Disease report\n";
	for (const auto& disease : _city->diseases())
	{
		std::cout << "\t" << colourName(disease) << "(" << colourAbbreviation(disease) << "): " << _city->diseaseCubes(disease) << " cubes\n";
	}
}

bool action::TreatDisease::isValid() const
{
	return _performer && _city;
}
