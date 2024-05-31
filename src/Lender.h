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
    explicit Lender(const string& name);

    // Getters
    string getName() const;
    Portfolio* getPortfolio();

    // Other methods
    void display();

    // Serialization
    void serialize(ostream& out) const;
    static Lender* deserialize(istream& in);

private:
    string name;
    Portfolio* portfolio;
};

#endif // LENDER_H


