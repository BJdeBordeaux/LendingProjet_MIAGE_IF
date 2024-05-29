#ifndef LENDER_H
#define LENDER_H

#include <string>
#include <vector>
#include "Facility.h"
#include "Account.h"
#include "Portfolio.h"

using namespace std;

class Lender {
public:
    // Constructor
    Lender(const string& name);

    // Getters
    string getName() const;
    Portfolio* getPortfolio();

private:
    string name;
    Portfolio* portfolio;
};

#endif // LENDER_H


