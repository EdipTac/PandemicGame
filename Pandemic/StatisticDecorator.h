#pragma once
#include "GameStatistics.h"

class StatisticDecorator : public GameStatistics {
protected:
	GameStatistics *_statistic;
public:
	StatisticDecorator(GameStatistics *sta);
	~StatisticDecorator();

};