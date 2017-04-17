#include "Medic.h"
#include "City.h"
#include "Board.h"

const std::string desc =
	"The Medic removes ALL cubes, not 1, of the same color when doing the Treat Disease action.\n"
	"If a disease has been cured, he automatically removes all cubes of that color from a city,\n"
	"simply by entering it or being there.This does not take an action.\n"
	"Note: The Medic’s automatic removal of cubes can occur on other players’ turns, if he is  \n"
	"moved by the Dispatcher or the Airlift Event. The Medic also prevents placing disease     \n"
	"cubes (and outbreaks) of CURED diseases in his location.";

role::Medic::Medic()
	: RoleCard { "Medic", desc, "Orange" }
{}

role::Medic::~Medic() {}

void role::Medic::onEnter(City& city) const
{
	for (const auto& colour : colours())
	{
		if (Board::instance().isCured(colour) && city.diseaseCubes(colour) > 0)
		{
			city.removeAllDiseaseCubes(colour, Board::instance().cubePool());
		}
	}
}

void role::Medic::treatDisease(City& city, const Colour& colour) const
{
	city.removeAllDiseaseCubes(colour, Board::instance().cubePool());
}
