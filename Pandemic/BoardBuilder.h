#pragma once
#include "json.hpp"
#include "Map.h"
#include <memory>

using json = nlohmann::json;

std::unique_ptr<Map> readMapFromFile(const std::string& fileName);

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