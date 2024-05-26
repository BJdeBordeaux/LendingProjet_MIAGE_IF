#include "Deal.h"

// Constructor
Deal::Deal(const std::string& contractNumber, const std::string& agent, const std::vector<std::string>& pool,
           const std::string& borrower, double projectAmount, const std::string& currency,
           const std::string& startDate, const std::string& endDate, const std::string& status)
        : contractNumber(contractNumber), agent(agent), pool(pool), borrower(borrower),
          projectAmount(projectAmount), currency(currency), startDate(startDate), endDate(endDate), status(status) {}

// Getters
std::string Deal::getContractNumber() const {
    return contractNumber;
}

std::string Deal::getAgent() const {
    return agent;
}

std::vector<std::string> Deal::getPool() const {
    return pool;
}

std::string Deal::getBorrower() const {
    return borrower;
}

double Deal::getProjectAmount() const {
    return projectAmount;
}

std::string Deal::getCurrency() const {
    return currency;
}

std::string Deal::getStartDate() const {
    return startDate;
}

std::string Deal::getEndDate() const {
    return endDate;
}

std::string Deal::getStatus() const {
    return status;
}

std::vector<Facility>& Deal::getFacilities() {
    return facilities;
}

// Other methods
void Deal::addFacility(const Facility& facility) {
    facilities.push_back(facility);
}

double Deal::calculateTotalAmount() const {
    double totalAmount = 0;
    for (const auto& facility : facilities) {
        totalAmount += facility.getAmount();
    }
    return totalAmount;
}
