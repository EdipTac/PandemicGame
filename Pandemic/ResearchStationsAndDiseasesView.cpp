#include "ResearchStationsAndDiseasesView.h"

ResearchStationsAndDiseasesView::ResearchStationsAndDiseasesView(GameState* gameState)
	:_subject{ gameState } 
{
	_subject->attach(*this);
}

ResearchStationsAndDiseasesView::~ResearchStationsAndDiseasesView() {}

void ResearchStationsAndDiseasesView::update() 
{

}

GameState* ResearchStationsAndDiseasesView::subject() const
{
	return _subject;
}