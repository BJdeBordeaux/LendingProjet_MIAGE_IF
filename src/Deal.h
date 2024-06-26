#ifndef DEAL_H
#define DEAL_H

#include <string>
#include <vector>
#include "Facility.h"

using namespace std;

class Deal {
public:
    // Constructor
    Deal(string  contractNumber, string  agent, const vector<string>&  borrowers, vector<Facility* > facilities); // multiple borrowers
//    Deal(string  contractNumber, string  agent, vector<Facility* > facilities); // multiple borrowers

    // Getters
    string getContractNumber() const;
    string getAgent() const;
    vector<string> getPool() const;
    vector<string> getBorrowers() const;
    vector<double> getProjectAmounts() const;
    vector<string> getCurrencies() const;
    string getStartDate() const;
    string getEndDate() const;
    string getStatus() const;
    vector<Facility*> getFacilities();

    // Other methods
    Facility* addFacility(Facility* facility);
    string addBorrower(string borrower);
    void display(bool displayFacilities = false);

    // Serialization
    void serialize(ostream& out) const;
    static Deal* deserialize(istream& in);

private:
    string contractNumber;
    string agent;
    vector<string> pool;
    vector<string> borrowers;
    vector<double> projectAmounts;
    vector<string> currencies;
    string startDate;
    string endDate;
    string status;
    vector<Facility*> facilities;
};

#endif // DEAL_H
