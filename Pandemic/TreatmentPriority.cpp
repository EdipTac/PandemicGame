#include "TreatmentPriority.h"
#include <iostream>
#include <utility>
#include <algorithm>


using namespace std;

TreatmentPriority::TreatmentPriority(GameStatistics *dec)
	: StatisticDecorator(dec)
{
	Board::instance().subscribe(*this);
}
void TreatmentPriority::update() {

	TreatmentPriority::display();
}
bool TreatmentPriority::sortbysec(const pair<City*, int> &a, const pair<City*, int> &b)
{
	return (a.second > b.second);
}

void TreatmentPriority::display() {
	cout << "\nTreatment priority in descending order for \ncities which have more than two disease cubes:" << endl;
	vector <pair<City*, int>> citylist;
	for (auto& city : Board::instance().map().cities()) {

		citylist.push_back(make_pair(city.get(), city->totalCubes()));
	}
	sort(citylist.begin(), citylist.end(), sortbysec);
	for (int i = 0; i<citylist.size(); i++)
	{
		if (citylist[i].second >= 1) {
			cout << citylist[i].first->name() << endl;
			for (auto& color : citylist[i].first->diseases()) {
				cout << "has " << citylist[i].first->diseaseCubes(color) << " " << colourName(color) << " disease cube(s)" << endl;
			}
		}
	}
};

