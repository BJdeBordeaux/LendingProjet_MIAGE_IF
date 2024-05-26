#ifndef FACILITY_H
#define FACILITY_H

#include <string>
#include <vector>
#include "Part.h"

class Facility {
public:
    // Constructor
    Facility(const std::string& startDate, const std::string& endDate, double amount, const std::string& currency,
             const std::vector<std::string>& lenders);

    // Getters
    std::string getStartDate() const;
    std::string getEndDate() const;
    double getAmount() const;
    std::string getCurrency() const;
    std::vector<std::string> getLenders() const;
    std::vector<Part>& getParts();

    // Other methods
    void addPart(const Part& part);
    double calculateInterest() const;
    double getRemainingAmount() const;

private:
    std::string startDate;
    std::string endDate;
    double amount;
    std::string currency;
    std::vector<std::string> lenders;
    std::vector<Part> parts;
};

#endif // FACILITY_H
