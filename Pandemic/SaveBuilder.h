#pragma once
#include "json.hpp"

using json = nlohmann::json;

class SaveBuilder {
public:
	void persist(const std::string& fileName);

	SaveBuilder& saveMap();
	SaveBuilder& savePlayers();
	SaveBuilder& saveCities();
	SaveBuilder& saveInfectionCards();
	SaveBuilder& savePlayerCards();
protected:
	json gameFile;
};