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
    vector<Part*> getParts();

    // Other methods
    Part* addPart(Part* part);
    double calculateInterest(const string& lender);
    double calculateTotalInterest();
    double calculateRemainingInterestAmount();
    void display(bool displayLenders = false);

    // Serialization
    void serialize(ostream& out) const;
    static Facility* deserialize(istream& in);

private:
    string startDate;
    string endDate;
    string currency;
    vector<string> lenders;
    vector<double> lenderAmounts;
    vector<Part*> parts;
};

#endif // FACILITY_H
