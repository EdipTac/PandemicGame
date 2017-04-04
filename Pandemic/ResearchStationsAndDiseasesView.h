#pragma once
#include <vector>
#include "Observer.h"
#include "ResearchStationsAndDiseases.h"



class ResearchStationsAndDiseasesView : public Observer
{
public:
	ResearchStationsAndDiseasesView();
	ResearchStationsAndDiseasesView(ResearchStationsAndDiseases* r);
	~ResearchStationsAndDiseasesView();
	/*void update() override;
	void display();*/

private:
	ResearchStationsAndDiseases *_subject;
};

