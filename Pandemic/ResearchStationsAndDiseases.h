#pragma once
#include <vector>
#include <iostream>


#include "Observable.h"
#include "GameState.h"
#include "CubePool.h"

class ResearchStationsAndDiseases : public Observable 
{
public:
	ResearchStationsAndDiseases();
	~ResearchStationsAndDiseases();
	void removeResearchStation();
	int getRemainingStations();
	int getRemainingCubes();
	void update();
	void display();
	/*void addDiseaseCube(int nbcubes);
	void addResearchStation();*/

private:
	int _cubesRemaining;
	int _stationsRemaining;
	std::vector<int> _cubes;
};

