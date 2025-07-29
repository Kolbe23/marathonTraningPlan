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
    string skillLevel;
    char colon;
    int goalHr;
    string minutes;
    int goalTime;

    Plan trainingPlan;

    cout << "What is your preferred skill level for your marathon training plan? \n"
         << "Please enter one of these three options: beginner, intermediate, or advanced:\n";
    cin >> skillLevel;

    while (skillLevel[0] != 'i' && skillLevel[0] != 'b' && skillLevel[0] != 'a') {
        cout << "Please enter only intermediate, beginner, or advanced:\n";
        cin >> skillLevel;
    }

    cout << "Your goal time must be under 6 hours and 30 minutes.\n";
    cout << "What is your goal time? Please enter in h:mm format:\n\n";
    cin >> goalHr >> colon >> minutes;

    goalTime = ((goalHr * 60) + stoi(minutes));

    cout << "Your goal time is to be under: " << goalHr << colon << minutes << endl;

    trainingPlan.printPlan(skillLevel[0], goalTime);  // generates plan.json

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