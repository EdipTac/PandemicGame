#include "Scientist.h"

const std::string desc =
	"The Scientist needs only 4 (not 5) City cards of the same disease color to Discover a Cure for that disease.";

role::Scientist::Scientist()
	: RoleCard { "Scientist", desc, "White" }
{}

role::Scientist::~Scientist() {}

int role::Scientist::numCardsNeededToCure() const
{
	return 4;
}
