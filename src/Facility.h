#ifndef FACILITY_H
#define FACILITY_H

#include <string>
#include <vector>
#include "Part.h"
using namespace std;

class Facility {
public:
    // Constructor
    Facility(string  startDate, string  endDate, vector<double> lenderAmounts, string  currency,
             vector<string> lenders);

    // Getters
    string getStartDate();
    string getEndDate();
    string getCurrency();
    vector<string> getLenders();
    vector<double> getLenderAmounts();
    double getTotalAmount();
    vector<Part>& getParts();

    // Other methods
//    void addPart(const Part& part);
    double calculateInterest(const string& lender);
//    double getRemainingAmount();

private:
    string startDate;
    string endDate;
    string currency;
    vector<string> lenders;
    vector<double> lenderAmounts;
    vector<Part> parts;
};

#endif // FACILITY_H
