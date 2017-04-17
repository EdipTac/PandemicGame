#include <string>
#include <vector>
#include <memory>
#include <cstdlib>
#include <ctime>

#include "Dispatcher.h"
#include "ContingencyPlanner.h"
#include "OperationsExpert.h"
#include "RoleCard.h"
#include "DeckOfRoles.h"
#include "Researcher.h"
#include "Medic.h"
#include "QuarantineSpecialist.h"
#include "Scientist.h"
#include "Util.h"

using namespace role;

DeckOfRoles::DeckOfRoles()
{	
	_drawPile.push_back(std::make_unique<ContingencyPlanner>());
	_drawPile.push_back(std::make_unique<Dispatcher>());
	_drawPile.push_back(std::make_unique<Medic>());
	_drawPile.push_back(std::make_unique<OperationsExpert>());
	_drawPile.push_back(std::make_unique<QuarantineSpecialist>());
	_drawPile.push_back(std::make_unique<Researcher>());
	_drawPile.push_back(std::make_unique<Scientist>());
}

std::vector<std::unique_ptr<RoleCard>> role::cards()
{
	std::vector<std::unique_ptr<RoleCard>> v;
	v.push_back(std::make_unique<ContingencyPlanner>());
	v.push_back(std::make_unique<Dispatcher>());
	v.push_back(std::make_unique<Medic>());
	v.push_back(std::make_unique<OperationsExpert>());
	v.push_back(std::make_unique<QuarantineSpecialist>());
	v.push_back(std::make_unique<Researcher>());
	v.push_back(std::make_unique<Scientist>());
	shuffle(v);
	return v;
}
