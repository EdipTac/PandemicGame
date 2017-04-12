#include "QuarantineSpecialist.h"
#include "City.h"

const std::string desc =
	"The Quarantine Specialist prevents both outbreaks and "
	"the placement of disease cubes in the city she is in "
	"and all cities connected to that city.\nShe does not affect"
	"cubes placed during setup.";

role::QuarantineSpecialist::QuarantineSpecialist()
	: RoleCard { "Quarantine Specialist", desc, "Dark Green" }
{}

role::QuarantineSpecialist::~QuarantineSpecialist() {}

void role::QuarantineSpecialist::onEnter(City& city) const
{
	city.isQuarantined(true);
}

void role::QuarantineSpecialist::onExit(City& city) const
{
	city.isQuarantined(false);
}
