#include"Plan.h"
#include<iostream>
#include<cmath>
#include<vector>
#include<map>
#include<string>
using namespace std;
void Plan::printPlan(const char& level,const int &goalTime) {
	if(level == 'b'){
		trainingLevel = Level::beginner;
	}
	else if(level == 'i'){
		trainingLevel = Level::intermediate;
	}
	else{
		trainingLevel = Level::advanced;
	}
	cout << "Week\t Mon\t Tues\t Wed\t Thur\t Fri\t Sat \t Sun\t Total Miles\n";

	//create output vector:
	vector<vector<pair<string,string>>> output;
	

	for(int i = 1; i <= 16; ++i){
		//create map for each week
		vector<pair<string, string>> weekData;

		int tues = getTuesMileage(i);
		int thurs = getThurMiles(i);
		int sat = getSatMiles(i);
		int sun = getSunMiles(i);
		int wedInt = 0;
		int friInt = 0;
		string fri ="Rest";
		string wed ="Rest";
		string mon ="Rest";
		int weeklyTotal = 0;
		switch(trainingLevel){
			case(Level::beginner):
				weeklyTotal = tues + thurs + sat + sun;

				//create map of data to send to python script to make into excel spreadsheet
				weekData.emplace_back("Week",to_string(i));
				weekData.emplace_back("Monday",mon);
				weekData.emplace_back("Tuesday",to_string(tues));
				weekData.emplace_back("Wednesday",wed);
				weekData.emplace_back("Thursday",to_string(thurs));
				weekData.emplace_back("Friday",fri);
				weekData.emplace_back("Saturday",to_string(sat));
				weekData.emplace_back("Sunday",to_string(sun));
				weekData.emplace_back("Total miles",to_string(weeklyTotal));
				output.push_back(weekData);
				break;

			case(Level::intermediate):
				wedInt = tues;
				if(i != 16){
					tues +=3;
					thurs += 3;
					sun += 4;
				}
				weeklyTotal = tues + wedInt + thurs + sat + sun;

				//create map of data to send to python script to make into excel spreadsheet
				
				weekData.emplace_back("Week",to_string(i));
				weekData.emplace_back("Monday",mon);
				weekData.emplace_back("Tuesday",to_string(tues));
				weekData.emplace_back("Wednesday",to_string(wedInt));
				weekData.emplace_back("Thursday",to_string(thurs));
				weekData.emplace_back("Friday",fri);
				weekData.emplace_back("Saturday",to_string(sat));
				weekData.emplace_back("Sunday",to_string(sun));
				weekData.emplace_back("Total miles",to_string(weeklyTotal));
				output.push_back(weekData);

				break;
			case(Level::advanced):
				wedInt = tues;
				if(i != 16){
					friInt = tues;
					tues +=3;
					thurs += 3;
					sun += 4;
				}
				weeklyTotal = friInt + tues + wedInt + thurs + sat + sun;

				//create map of data to send to python script to make into excel spreadsheet

				weekData.emplace_back("Week",to_string(i));
				weekData.emplace_back("Monday",mon);
				weekData.emplace_back("Tuesday",to_string(tues));
				weekData.emplace_back("Wednesday",to_string(wedInt));
				weekData.emplace_back("Thursday",to_string(thurs));
				weekData.emplace_back("Friday",to_string(friInt));
				weekData.emplace_back("Saturday",to_string(sat));
				weekData.emplace_back("Sunday",to_string(sun));
				weekData.emplace_back("Total miles",to_string(weeklyTotal));
				output.push_back(weekData);

				
		}
	}

	for (const auto& week : output) {
		cout << "{ ";
		for (const auto& [key, value] : week) {
			cout << "\"" << key << "\": \"" << value << "\", ";
		}
		cout << "}\n";
	}
	printPaces(goalTime);
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
	else { //only occur for last week (race week!!)
		mileage = 3;
	}
	return mileage;
}

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
		if(week == 2 || weekGrouping == 1){
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
void Plan::printPaces(const int& goal){
	double minPerMile = goal / 26.2;
	//race pace
	int racePaceMin = static_cast<int>(minPerMile);
	int racePaceSec =  static_cast<int>((minPerMile-racePaceMin) * 60);
	string racePace = to_string(racePaceMin) + ":" + (racePaceSec < 10 ? "0" : "") + to_string(racePaceSec);
	cout << "Your race pace is: " << racePace <<  " min/mile\n";
	//tempo pace
	double fastDay = minPerMile - .75;
	int fastDayMin = static_cast<int>(fastDay);
	int fastDaySec =  static_cast<int>((fastDay-fastDayMin) * 60);
	string fastPace = to_string(fastDayMin) + ":" + (fastDaySec < 10 ? "0" : "") + to_string(fastDaySec);
	cout << "Fast day pace: " << fastPace << " min/mile\n";
	//long run pace
	double longRunFloor = minPerMile + .5;
	double longRunCeiling = minPerMile + 1.5;
	int lrfMin = static_cast<int>(longRunFloor);
	int lrcMin = static_cast<int>(longRunCeiling);
	int lrfSec =  static_cast<int>((longRunFloor-lrfMin) * 60);
	int lrcSec =  static_cast<int>((longRunCeiling-lrcMin) * 60);
	string longRunFloorPace = to_string(lrfMin) + ":" + (lrfSec < 10 ? "0" : "") + to_string(lrfSec);
	string longRunCeilingPace = to_string(lrcMin) + ":" + (lrcSec < 10 ? "0" : "") + to_string(lrcSec);
	cout << "Long run and chill pace: " << longRunFloorPace << "-" << longRunCeilingPace << " min/mile\n"; 
}

