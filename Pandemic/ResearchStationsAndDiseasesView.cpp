#include "ResearchStationsAndDiseasesView.h"


ResearchStationsAndDiseasesView::ResearchStationsAndDiseasesView() {};

ResearchStationsAndDiseasesView::ResearchStationsAndDiseasesView(ResearchStationsAndDiseases* r)

{
	_subject = r;
	_subject->attach(this);
}

ResearchStationsAndDiseasesView::~ResearchStationsAndDiseasesView() {
	_subject->detach(this);
}

void ResearchStationsAndDiseasesView::update() 
{
	display();
}

void ResearchStationsAndDiseasesView::display() {
	int cubes = _subject->getRemainingCubes();
	int stations = _subject->getRemainingStations();
	std::cout << "There are currently " << cubes << " cubes and " << stations << " stations remaining. \n";
}
