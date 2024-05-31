#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include <vector>
#include "Part.h"
#include "Facility.h"
#include "Account.h"

using namespace std;

class Portfolio {
public:
    // Constructor
    Portfolio(string  lender, const vector<Facility*>& facilities);
    explicit Portfolio(string  lender);

    // getters and setters
    string getLender() const;
    vector<Facility*> getFacilities() const;
    vector<double> getAllCurrencyInterests() const;
    vector<string> getAllCurrencies() const;
    vector<Account*> getCurrencyAccounts() const;

    // search methods
    Account* getAccountByCurrency(const string& currency);

    // Other methods
    Facility *addFacility(Facility* facility);
    double recalculateCurrencyInterest(const string& currency);
    void display();

    // Serialization
    void serialize(ostream& out) const;
    static Portfolio* deserialize(istream& in);

private:
    string lender;
    vector<Facility*> facilities;
    vector<Account*> currencyAccounts;
};

#endif // PORTFOLIO_H
