#pragma once
#include "StatisticDecorator.h"

class InfectedCityPercentage : public StatisticDecorator {
public: InfectedCityPercentage(GameStatistics *dec);
		void update();
		void display();
};
