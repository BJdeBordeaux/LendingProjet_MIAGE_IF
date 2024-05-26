#include <algorithm>
#include "Utils.h"

// Split a string by a delimiter
std::vector<std::string> Utils::splitString(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string item;
    while (std::getline(ss, item, delimiter)) {
        tokens.push_back(item);
    }
    return tokens;
}

// Convert a string to uppercase
std::string Utils::toUpperCase(const std::string& str) {
    std::string upperStr = str;
    std::transform(upperStr.begin(), upperStr.end(), upperStr.begin(), ::toupper);
    return upperStr;
}

// Format a date string into a specified format
std::string Utils::formatDate(const std::string& date, const std::string& format) {
    std::tm tm = {};
    std::istringstream ss(date);
    ss >> std::get_time(&tm, "%Y-%m-%d");
    std::ostringstream oss;
    oss << std::put_time(&tm, format.c_str());
    return oss.str();
}

// Get the current date in YYYY-MM-DD format
std::string Utils::getCurrentDate() {
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d");
    return oss.str();
}
