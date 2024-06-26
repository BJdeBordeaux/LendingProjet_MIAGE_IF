#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <ctime>
#include "Utils.h"

using namespace std;

// Split a string by a delimiter
vector<string> Utils::splitString(const string& str, char delimiter) {
    vector<string> tokens;
    stringstream ss(str);
    string item;
    while (getline(ss, item, delimiter)) {
        tokens.push_back(item);
    }
    return tokens;
}

// Convert a string to uppercase
string Utils::toUpperCase(const string& str) {
    string upperStr = str;
    transform(upperStr.begin(), upperStr.end(), upperStr.begin(), ::toupper);
    return upperStr;
}

// Format a date string into a specified format
string Utils::formatDate(const string& date, const string& format) {
    tm tm = {};
    istringstream ss(date);
    ss >> get_time(&tm, "%Y-%m-%d");
    ostringstream oss;
    oss << put_time(&tm, format.c_str());
    return oss.str();
}

// Get the current date in YYYY-MM-DD format
string Utils::getCurrentDate() {
    auto t = time(nullptr);
    auto tm = *localtime(&t);
    ostringstream oss;
    oss << put_time(&tm, "%Y-%m-%d");
    return oss.str();
}

// Function to parse a date string in the format "YYYY-MM-DD" to a tm structure
tm Utils::parseDate(const string& dateStr) {
    tm tm = {};
    stringstream ss(dateStr);
    ss >> get_time(&tm, "%Y-%m-%d");
    tm.tm_hour = 0;
    tm.tm_min = 0;
    tm.tm_sec = 0;
    return tm;
}

// Function to calculate the difference in days between two dates
int Utils::dateDifference(const string& dateStr1, const string& dateStr2) {
    tm tm1 = parseDate(dateStr1);
    tm tm2 = parseDate(dateStr2);
    time_t time1 = mktime(&tm1);
    time_t time2 = mktime(&tm2);
    double difference = difftime(time2, time1);
    return static_cast<int>(difference / (60 * 60 * 24));
}

// Function to calculate the difference in days between a given date and today
int Utils::dateDifferenceTodayMinusADate(const string& dateStr) {
    time_t t = time(nullptr);
    tm tmNow = *localtime(&t);
    tm tmDate = parseDate(dateStr);
    time_t timeNow = mktime(&tmNow);
    time_t timeDate = mktime(&tmDate);
    double difference = difftime(timeNow, timeDate);
    return static_cast<int>(difference / (60 * 60 * 24));
}

string Utils::trim(const string &s) {
    string::const_iterator it = s.begin();
    while (it != s.end() && isspace(*it))
        it++;

    string::const_reverse_iterator rit = s.rbegin();
    while (rit.base() != it && isspace(*rit))
        rit++;

    return std::string(it, rit.base());
}

int Utils::getIntInput(const string &prompt) {
    int num;
    cout << prompt << endl;
    cin >> num;

    while (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input. Please enter an integer." << endl;
        cin >> num;
    }
    cin.ignore(1000, '\n');
    return num;
}

double Utils::getMoneyInput(const string &prompt) {
    double num;
    cout << prompt << endl;
    cin >> num;

    while (cin.fail() || num < 0) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input. Please enter a positive number." << endl;
        cin >> num;
    }
    cin.ignore(1000, '\n');
    return num;
}

char Utils::getALetterInput(const string &prompt) {
    char c;
    cout << prompt << endl;
    cin >> c;

    while (cin.fail() || !isalpha(c)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input. Please enter a letter." << endl;
        cin >> c;
    }
    cin.ignore(1000, '\n');
    // convert to lowercase
    char c_lower = char (tolower(c));
    return c_lower;
}

string Utils::getDateInput(const string &prompt) {
    string date;
    cout << prompt << endl;
    cin >> date;

    while (cin.fail() || date.length() != 10 || date[4] != '-' || date[7] != '-') {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input. Please enter a date in the format YYYY-MM-DD:" << endl;
        cin >> date;
        // convert it to tm, if fails, it will ask to input again
        parseDate(date);
    }
    cin.ignore(1000, '\n');
    return date;
}

string Utils::getContractNumber(const string &prompt) {
    // contract number should be in the format : a letter (S,Z,B) following by 4 digits
    string contractNumber;
    cout << prompt << endl;
    cin >> contractNumber;

    while (cin.fail() || contractNumber.length() != 5 || (contractNumber[0]!= 'S' && contractNumber[0]!= 'Z' && contractNumber[0]!= 'B') || !isdigit(contractNumber[1]) || !isdigit(contractNumber[2]) || !isdigit(contractNumber[3]) || !isdigit(contractNumber[4])) {
        // if the first letter is not S, Z or B, it will ask to input again
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input. Please enter a contract number in the format: a letter (S,Z,B) following by 4 digits." << endl;
        cin >> contractNumber;
    }

    cin.ignore(1000, '\n');
    return contractNumber;
}

string Utils::getStringInput(const string &prompt) {
    string buffer;
    cout << prompt << endl;
    getline(cin >> ws, buffer);
    return buffer;
}