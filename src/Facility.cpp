#include "Facility.h"

// Constructor
Facility::Facility(const std::string& startDate, const std::string& endDate, double amount, const std::string& currency,
                   const std::vector<std::string>& lenders)
        : startDate(startDate), endDate(endDate), amount(amount), currency(currency), lenders(lenders) {}

// Getters
std::string Facility::getStartDate() const {
    return startDate;
}

std::string Facility::getEndDate() const {
    return endDate;
}

double Facility::getAmount() const {
    return amount;
}

std::string Facility::getCurrency() const {
    return currency;
}

std::vector<std::string> Facility::getLenders() const {
    return lenders;
}

std::vector<Part>& Facility::getParts() {
    return parts;
}

// Other methods
void Facility::addPart(const Part& part) {
    parts.push_back(part);
}

double Facility::calculateInterest() const {
    double totalInterest = 0;
    for (const auto& part : parts) {
        totalInterest += part.getInterest();
    }
    return totalInterest;
}

double Facility::getRemainingAmount() const {
    double totalRepaid = 0;
    for (const auto& part : parts) {
        totalRepaid += part.getRepaidAmount();
    }
    return amount - totalRepaid;
}
