#pragma once
#include "StatisticDecorator.h"

class RemainingInfectionCard : public StatisticDecorator {
public: RemainingInfectionCard(GameStatistics *dec);
		void update();
		void display();
};