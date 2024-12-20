//#pragma once
#include<iostream>
#include<cmath>
#include<string>
//TODO enum class for beginner, intermediate, advanced
using namespace std;
class Plan{
private:
	char lvl;
	int week;
	int mondayMiles;
	int thurMiles;
	int tuesdayMiles;
	string racepace;
	int wednesdayMiles;
	int goalPace;
	int pace;
	string printPace;
	
public:
	void printPlan(const char& level, const int& goalTime);
	int getTuesMileage(int& week);
	int getThurMiles(int& week);
	int getSatMiles(int& week);
	int getSunMiles(int& week);
	void printPaces(const int& goal);
};

