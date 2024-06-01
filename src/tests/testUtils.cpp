#include <algorithm>
#include <iostream>
#include <string>
#include "../utils/Utils.h"

using namespace std;
int main() {
    string dateStr1 = "2024-01-01";
    string dateStr2 = "2024-05-01";

    int diff = Utils::dateDifference(dateStr1, dateStr2);
    cout << "Difference between " << dateStr1 << " and " << dateStr2 << " is " << diff << " days." << endl;

    string dateStr3 = "2024-05-01";
    int diffFromToday = Utils::dateDifferenceTodayMinusADate(dateStr3);
    cout << "Difference between today and " << dateStr3 << " is " << diffFromToday << " days." << endl;

    // test get input
    int num = Utils::getIntInput("Enter an integer:");
    cout << "You entered: " << num << endl;

    double money = Utils::getMoneyInput("Enter a positive number:");
    cout << "You entered: " << money << endl;

    char c = Utils::getALetterInput("Enter a letter:");
    cout << "You entered: " << c << endl;

    string date = Utils::getDateInput("Enter a date in the format YYYY-MM-DD:");
    cout << "You entered: " << date << endl;

    string contractNumber = Utils::getContractNumber("Enter a contract number:");
    cout << "You entered: " << contractNumber << endl;

    string agent = Utils::getStringInput("Enter agent:");
    cout << "You entered: " << agent << endl;

    return 0;
}

