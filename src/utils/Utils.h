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

    // trim white space
    static string trim(const string &s);

    // get an integer as input
    static int getIntInput(const string &prompt);

    // get a double as input for money
    static double getMoneyInput(const string &prompt);

    // get the first character of a string input, this char should be a letter
    static char getALetterInput(const string &prompt);

    // get date input
    static string getDateInput(const string &prompt);

    // get contract number
    static string getContractNumber(const string &prompt);

    // get line string input
    static string getStringInput(const string &prompt);

};

#endif // UTILS_H
