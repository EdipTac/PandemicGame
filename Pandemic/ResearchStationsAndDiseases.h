#pragma once
#include <vector>
#include "Observable.h"
#include "GameState.h"
#include "CubePool.h"


class ResearchStationsAndDiseases : public Observable 
{
public:
	ResearchStationsAndDiseases();
	unsigned researchStations() const;
	void removeResearchStation();
	void returnResearchStation();
	bool hasResearchStation() const;

private:
	int cubesRemaining;
	int stationsRemaining;
	CubePool _cubePool;
};

