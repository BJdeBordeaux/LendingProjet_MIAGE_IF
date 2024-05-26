#ifndef DEAL_H
#define DEAL_H

#include <string>
#include <vector>
#include "Facility.h"

class Deal {
public:
    // Constructor
    Deal(const std::string& contractNumber, const std::string& agent, const std::vector<std::string>& pool,
         const std::string& borrower, double projectAmount, const std::string& currency,
         const std::string& startDate, const std::string& endDate, const std::string& status);

    // Getters
    std::string getContractNumber() const;
    std::string getAgent() const;
    std::vector<std::string> getPool() const;
    std::string getBorrower() const;
    double getProjectAmount() const;
    std::string getCurrency() const;
    std::string getStartDate() const;
    std::string getEndDate() const;
    std::string getStatus() const;
    std::vector<Facility>& getFacilities();

    // Other methods
    void addFacility(const Facility& facility);
    double calculateTotalAmount() const;

private:
    std::string contractNumber;
    std::string agent;
    std::vector<std::string> pool;
    std::string borrower;
    double projectAmount;
    std::string currency;
    std::string startDate;
    std::string endDate;
    std::string status;
    std::vector<Facility> facilities;
};

#endif // DEAL_H
