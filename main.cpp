#include"Plan.h"
#include<iostream>
#include<cmath>
#include <cstdlib>   // for system()
#include<string>
using namespace std;


int main(int argc, char** argv) {
    if (argc != 2) {
        cerr << "Usage: ./main <excel_output_filename>\n";
        return 1;
    }

    string excelOutputFile = argv[1];

    // Collect user input and generate plan.json
    int skillLevel;
	char skillLevelChar;
    char colon;
    int goalHr;
    string minutes;
    int goalTime;

    Plan trainingPlan;
	//changed to ask user for how many days they'd like to run rather than a skill level
    cout << "How many days per week would you like to run? \n"
		<< "Please enter one of these three options: 4, 5, or 6\n";
	cin >> skillLevel;
	while (skillLevel != 4 && skillLevel != 5  && skillLevel != 6) {
		cout << "Please enter only 4, 5, or 6:\n";
		cin >> skillLevel;
	}
	//create character to correspond to requested days of training to keep compatible with earlier implementation
    if(skillLevel == 4){
        skillLevelChar = 'b';
    }
    else if(skillLevel == 5){
        skillLevelChar = 'i';
    }
    else{
        skillLevelChar = 'a';
    }

    cout << "Your goal time must be under 6 hours and 30 minutes.\n";
    cout << "What is your goal time? Please enter in h:mm format:\n\n";
    cin >> goalHr >> colon >> minutes;

    goalTime = ((goalHr * 60) + stoi(minutes));

    cout << "Your goal time is to be under: " << goalHr << colon << minutes << endl;

    trainingPlan.printPlan(skillLevelChar, goalTime);  // generates plan.json

    // Call Python script to convert plan.json → desired output
    string command = "python3 excel_writer.py plan.json " + excelOutputFile;
    int result = system(command.c_str());

    if (result != 0) {
        cerr << "❌ Failed to generate Excel file.\n";
    } else {
        cout << "✅ Excel file created: " << excelOutputFile << endl;
    }

    return 0;
}