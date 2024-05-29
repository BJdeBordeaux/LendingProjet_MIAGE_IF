#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <ctime>
using namespace std;
class Utils {
public:
    // Split a string by a delimiter
    static vector<string> splitString(const string& str, char delimiter);

    // Convert a string to uppercase
    static string toUpperCase(const string& str);

    // Format a date string into a specified format
    static string formatDate(const string& date, const string& format);

    // Get the current date in YYYY-MM-DD format
    static string getCurrentDate();

    // Parse a date string in the format "YYYY-MM-DD" to a std::tm structure
    static tm parseDate(const string& dateStr);

    // Calculate the difference in days between two dates
    static int dateDifference(const string& dateStr1, const string& dateStr2);

    // Calculate the difference in days between a given date and today
    static int dateDifferenceTodayMinusADate(const string& dateStr);
};

#endif // UTILS_H
