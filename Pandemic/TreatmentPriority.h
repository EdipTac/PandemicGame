#pragma once
#include "StatisticDecorator.h"
#include "City.h"
#include <utility>

class TreatmentPriority : public StatisticDecorator {
public: TreatmentPriority(GameStatistics *dec);
		void update();
		void display();
		static bool sortbysec(const std::pair<City*, int> &a, const std::pair<City*, int> &b);
};
