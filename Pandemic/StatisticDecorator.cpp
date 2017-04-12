#include "StatisticDecorator.h"
#include <iostream>

StatisticDecorator::StatisticDecorator(GameStatistics *sta) {
	_statistic = sta;
}
StatisticDecorator::~StatisticDecorator() {
};

