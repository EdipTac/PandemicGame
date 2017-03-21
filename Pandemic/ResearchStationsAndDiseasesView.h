#pragma once
#include <vector>
#include "Observer.h"
#include "GameState.h"


class ResearchStationsAndDiseasesView : public Observer
{
public:
	ResearchStationsAndDiseasesView(GameState* gameState);
	~ResearchStationsAndDiseasesView();

	void update() override;

	GameState* subject() const;

private:
	GameState* _subject;
};

