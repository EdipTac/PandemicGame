#include "Medic.h"

const std::string desc =
	"The Medic removes ALL cubes, not 1, of the same color"
	" when doing the Treat Disease action.\n"
	"If a disease has been cured, he automatically removes "
	"all cubes of that color from a city, simply by entering it "
	"or being there.This does not take an action.\n"
	"Note: The Medic�s automatic removal of cubes can occur on other players� \n"
	"turns, if he is moved by the Dispatcher or the Airlift Event.\n"
	"The Medic also prevents placing disease cubes (and outbreaks) of CURED diseases in his location";

role::Medic::Medic()
	: RoleCard { "Medic", desc, "Orange" }
{}

role::Medic::~Medic() {}