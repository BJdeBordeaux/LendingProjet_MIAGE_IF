#ifndef BORROWER_H
#define BORROWER_H

#include <string>
#include "Portfolio.h"
#include "Account.h"
#include "Deal.h"

class Borrower {
public:
    // Constructor
    Borrower(const std::string& name, const Account& account);

    // Getters
    std::string getName() const;
    Portfolio& getPortfolio();
    Account& getAccount();

    // Other methods
    void addDeal(const Deal& deal);

private:
    std::string name;
    Portfolio portfolio;
    Account account;
};

#endif // BORROWER_H
