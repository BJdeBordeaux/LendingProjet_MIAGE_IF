#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <ctime>
#include "Utils.h"
#include "../Account.h"

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

//int main() {
//    string dateStr1 = "2024-01-01";
//    string dateStr2 = "2024-05-01";
//
//    int diff = dateDifference(dateStr1, dateStr2);
//    cout << "Difference between " << dateStr1 << " and " << dateStr2 << " is " << diff << " days." << endl;
//
//    string dateStr3 = "2024-05-01";
//    int diffFromToday = dateDifferenceTodayMinusADate(dateStr3);
//    cout << "Difference between today and " << dateStr3 << " is " << diffFromToday << " days." << endl;
//
//    return 0;
//}

