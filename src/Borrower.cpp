#include "Borrower.h"

// Constructor
Borrower::Borrower(const std::string& name, const Account& account)
        : name(name), account(account) {}

// Getters
std::string Borrower::getName() const {
    return name;
}

Portfolio& Borrower::getPortfolio() {
    return portfolio;
}

Account& Borrower::getAccount() {
    return account;
}

// Other methods
void Borrower::addDeal(const Deal& deal) {
    // Implementation for adding a deal to the borrower's portfolio if necessary
}
