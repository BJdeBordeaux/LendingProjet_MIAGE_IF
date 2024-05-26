#include "Lender.h"

// Constructor
Lender::Lender(const std::string& name, const Account& account)
        : name(name), account(account) {}

// Getters
std::string Lender::getName() const {
    return name;
}

Account& Lender::getAccount() {
    return account;
}

std::vector<Facility>& Lender::getFacilities() {
    return facilities;
}

// Other methods
void Lender::participateInFacility(const Facility& facility) {
    facilities.push_back(facility);
}
