#ifndef DEAL_H
#define DEAL_H

#include <string>
#include <vector>
#include "Facility.h"

using namespace std;

class Deal {
public:
    // Constructor
    Deal(string  contractNumber, string  agent, const vector<string>& pool,
         string  borrower, double projectAmount, string  currency,
         string  startDate, string  endDate, string  status);
    Deal(string  contractNumber, string  agent, const vector<string>& pool,
         string  borrower, double projectAmount, string  currency,
         string  startDate, string  endDate);
    Deal(string  contractNumber, string  agent, string  borrower, string  currency, vector<Facility* > facilities);

    // Getters
    string getContractNumber() const;
    string getAgent() const;
    vector<string> getPool() const;
    string getBorrower() const;
    double getProjectAmount() const;
    string getCurrency() const;
    string getStartDate() const;
    string getEndDate() const;
    string getStatus() const;
    vector<Facility*> getFacilities();

    // Other methods
    Facility* addFacility(Facility* facility);
    double calculateTotalAmount() const;

private:
    string contractNumber;
    string agent;
    vector<string> pool;
    string borrower;
    double projectAmount;
    string currency;
    string startDate;
    string endDate;
    string status;
    vector<Facility*> facilities;
};

#endif // DEAL_H
