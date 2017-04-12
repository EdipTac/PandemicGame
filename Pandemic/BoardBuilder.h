#pragma once
#include "json.hpp"

using json = nlohmann::json;

class BoardBuilder {
public:
	BoardBuilder& loadBoard(std::string& gameSaveFile);

	BoardBuilder& loadPlayers();
	BoardBuilder& loadCities();
	BoardBuilder& loadInfectionCards();
	BoardBuilder& loadPlayerCards();
protected:
	json gameFile;
};