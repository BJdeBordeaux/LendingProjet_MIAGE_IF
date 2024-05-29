#ifndef BORROWER_H
#define BORROWER_H

#include <string>
#include "Portfolio.h"
#include "Account.h"
#include "Deal.h"

using namespace std;

class Borrower {
public:
    // Constructor
    Borrower(string  name);

    // Getters
    string getName() const;
    Portfolio* getPortfolio();

private:
    string name;
    Portfolio* portfolio;
};

#endif // BORROWER_H

