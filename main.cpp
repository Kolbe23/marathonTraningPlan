#include"Plan.h"
#include<iostream>
#include<cmath>
#include<string>
using namespace std;
int main(int argc, char** argv) {
	string skillLevel;
	char colon;
	char goalHr;
	string minutes;
	int hours;
	int goalTime;
	Plan trainingPlan;
	cout << "What is your preferred skill level for your marathon training plan? \n"
		<< "Please enter one of these three options: beginner, intermediate, or advanced:\n";
	cin >> skillLevel;
	while (skillLevel[0] != 'i' && skillLevel[0] != 'b'  && skillLevel[0] != 'a') {
		cout << "Please enter only intermediate, beginner, or advanced:\n";
		cin >> skillLevel;
	}
	cout << "Your goal time must be under 6 hours and 30 minutes.\n";
	cout << "What is your goal time? Please enter in h:mm format:\n";
	cin >> goalHr >> colon >> minutes;
	goalTime = (goalHr * 60 + stoi(minutes));
	trainingPlan.printPlan(skillLevel[0],goalTime);
	// cout << "tues \t thurs \t sat \t sun \n";
	// for(int i = 1; i <= 16; ++i){
	// 	cout << trainingPlan.getTuesMileage(i) << "\t" << trainingPlan.getThurMiles(i) << "\t" << 
	// 	trainingPlan.getSatMiles(i) << "\t" << trainingPlan.getSunMiles(i) <<  "\n";
	// }
}