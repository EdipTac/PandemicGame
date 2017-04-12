#include "InfectedCityPercentage.h"
#include <iostream>
using namespace std;

InfectedCityPercentage::InfectedCityPercentage(GameStatistics *dec)
	: StatisticDecorator(dec)
{
	Board::instance().subscribe(*this);
}
void InfectedCityPercentage::update() {

	InfectedCityPercentage::display();
}
void InfectedCityPercentage::display() {
	double rate = 100 * (Board::instance().infectedCityCounter() + 9) / 48.0;
	cout.setf(ios::fixed); cout.setf(ios::showpoint); cout.precision(2);
	cout << "\n"<< rate << " percentage of the cities are infected " << endl;
};