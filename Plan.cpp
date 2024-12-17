#include"Plan.h"
#include<iostream>
#include<cmath>
#include<string>
using namespace std;
void Plan::printPlan(const char& level,const int &goalTime) {
	cout << "Week\t Mon\t Tues\t Wed\t Thur\t Fri\t Sat \t Sun\t Total Miles\n";
	for(int i = 1; i <= 16; ++i){
		int tues = getTuesMileage(i);
		int thurs = getThurMiles(i);
		int sat = getSatMiles(i);
		int sun = getSunMiles(i);
		int weeklyTotal;
		if(level == 'b'){
			string fri ="Rest";
			string wed ="Rest";
			string mon ="Rest";
			weeklyTotal = tues + thurs + sat + sun;
			cout << i << "\t\t" << mon << " \t " << tues << "\t\t"
				<< wed << "\t\t" << thurs << "\t" << fri
				<< " \t " << sat << "\t\t" << sun   << "\t\t" << weeklyTotal << "\n";
		}
		else if(level == 'i'){
			int wed = tues;
			string fri ="Rest";
			string mon ="Rest";
			tues +=3;
			thurs += 3;
			sat += 3;
			sun += 4;
			weeklyTotal = tues + wed + thurs + sat + sun;
			cout << i << "\t\t" << mon << " \t " << tues << "\t\t"
				<< wed << "\t\t" << thurs << "\t\t" << fri
				<< " \t " << sat << "\t\t" << sun   << "\t\t" << weeklyTotal << "\n";
		}
	}
}
int Plan::getTuesMileage(int& week) {
	int mileage;
	if (week < 12) {
		mileage = 4;
	}
	else if (week < 15) {
		mileage = 5;
	}
	else if (week == 15) {
		mileage = 4;
	}
	else {
		mileage = 3;
	}
	return mileage;
}
void Plan::paces(){}
int Plan::getThurMiles(int& week) {
	int mileage = 4;
	int weekGrouping = floor(week/4);
	if(week % 4 == 3){ //easy weeks are 3, 7, 11, and 15
		if(weekGrouping == 2){ //only week 11 is 6 on thursday, other easty weeks are 4
			mileage += 2;
		}
		else{
			mileage += 0;
		}
	}
	else{
		if(week == 2 ||weekGrouping == 1){
			mileage += 2;
		}
		else if(weekGrouping == 2){
			mileage += 3;
		}
		else if(weekGrouping == 3){
			mileage += 4;
		}
		else if(week == 16){
			mileage -= 1; //this should only yield true for week 16; race week
		}
	}
	return mileage;
}
int Plan::getSatMiles(int& week){
	int mileage;
	bool lightWeek = week % 4 == 3;
	int weekGrouping = floor(week/4);
	if(weekGrouping == 0){
		mileage = 5;
		if(lightWeek){
			mileage -= 2;
		}
	}
	else if(weekGrouping == 1){
		mileage = 6;
		if(lightWeek){
			mileage -= 2;
		}
	}
	else if(weekGrouping == 2){
		mileage = 8;
		if(lightWeek){
			mileage -= 2;
		}
	}
	else if(weekGrouping == 3){
		mileage = 10;
		if(lightWeek){
			mileage = 3;
		}
	}
	else{
		mileage = 2;
	}
	return mileage;
}
int Plan::getSunMiles(int& week){
	int mileage;
	int weekGroup = floor(week/4);
	int lightWeek = week % 4 == 3;
	if(weekGroup == 0){
		mileage = 8;
		if(week == 2){
			mileage += 2;
		}
		if(lightWeek){
			mileage -= 2;
		}
	}
	else if(weekGroup == 1){ //for 2nd group of 4 weeks should be 10, 12, 14, 10
		mileage = 10;
		if(week % 4 == 0){
			mileage = 10;
			}
		else if(week % 4 == 1){
			mileage += 2;
		}
		else if(!lightWeek){
			mileage += 4;
		}
	}
	else if(weekGroup == 2 || weekGroup == 3){ //should print 14, 16, 18, 10
		mileage = 14;
		if(week % 4 == 0){
			mileage = 14;
			}
		else if(week % 4 == 1){
			mileage += 2;
		}
		else if(!lightWeek){
			mileage += 4;
		}
		else{
			mileage = 10; 
		}
	}
	else{
		mileage = 26.2;  //race day!!
	}
	return mileage;
}
