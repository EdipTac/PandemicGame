#include "ResearchStationsAndDiseases.h"
#include "GameState.h"


ResearchStationsAndDiseases::ResearchStationsAndDiseases()
	:_cubes{ 24,24,24,24}, _stationsRemaining{ 6 }
{};

ResearchStationsAndDiseases::~ResearchStationsAndDiseases() {};

void ResearchStationsAndDiseases::removeResearchStation() {
	_stationsRemaining = (_stationsRemaining + 1);
	notify();
}

int ResearchStationsAndDiseases::getRemainingCubes() {
	for (int i = 0; i < _cubes.size(); i++) {
		_cubesRemaining = _cubesRemaining + _cubes[i];
	}
	return (_cubesRemaining);
}

int ResearchStationsAndDiseases::getRemainingStations() {
	return (_stationsRemaining);
}

//void ResearchStationsAndDiseases::display() {
//	std::cout << "There are currently " << _cubesRemaining << " disease cubes and " << _stationsRemaining << " research stations that can be used. \n";
//	
//}
//		
//void ResearchStationsAndDiseases::update() {
//	display();
//}

//void ResearchStationsAndDiseases::addDiseaseCube(int nbcubes) {
//	if (nbcubes > getRemainingCubes()){
//		std::cout << "Sorry, there aren't enough cubes remaining to infect \n";
//	}
//	else {
//
//	}
//}