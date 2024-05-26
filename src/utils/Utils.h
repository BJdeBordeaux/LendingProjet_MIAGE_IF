#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <ctime>

class Utils {
public:
    // Static utility functions
    static std::vector<std::string> splitString(const std::string& str, char delimiter);
    static std::string toUpperCase(const std::string& str);
    static std::string formatDate(const std::string& date, const std::string& format);
    static std::string getCurrentDate();
};

#endif // UTILS_H
