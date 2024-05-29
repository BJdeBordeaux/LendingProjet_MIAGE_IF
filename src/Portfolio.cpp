#include "Portfolio.h"
#include <iostream>
#include <utility>
using namespace std;

Portfolio::Portfolio(string lender, const vector<Facility*>& facilities): lender(std::move(lender)){
    for (Facility* facility : facilities) {
        this->addFacility(facility);
    }
}

Portfolio::Portfolio(string  lender): lender(std::move(lender)){}

string Portfolio::getLender() const {
    return lender;
}

vector<Facility*> Portfolio::getFacilities() const {
    return facilities;
}

Account* Portfolio::getAccountByCurrency(const string& currency) {
    for (Account* account : currencyAccounts) {
        if (account->getCurrency() == currency) {
            return account;
        }
    }

    // If account not found, create a new account
    auto newAccount = new Account(currency);
    currencyAccounts.push_back(newAccount);
    return newAccount;
}

Facility *Portfolio::addFacility(Facility *facility) {
    // add Facility
    facilities.push_back(facility);
    // Update logic
    Account* account = getAccountByCurrency(facility->getCurrency());
    account->deposit(facility->calculateInterest(lender));
    return facility;
}

vector<double> Portfolio::getAllCurrencyInterests() const {
    auto allCurrencyInterests = vector<double>{};
    for (Account* account : currencyAccounts) {
        allCurrencyInterests.push_back(account->getBalance());
    }
    return allCurrencyInterests;
}

double Portfolio::recalculateCurrencyInterest(const string& currency) {
    Account* account = getAccountByCurrency(currency);
    double recalculatedCurrencyInterest = 0;
    for (Facility *facility : facilities) {
        if (facility->getCurrency() == currency) {
            recalculatedCurrencyInterest += facility->calculateInterest(lender);
        }
    }

    // Update the currency interest
    for(Account* accountToUpdate: currencyAccounts) {
        if(accountToUpdate->getCurrency() == currency) {
            accountToUpdate->setBalance(recalculatedCurrencyInterest);
        }
    }

    return recalculatedCurrencyInterest;
}

//int main(){
//
//    // test all methods
//    vector<double> lenderAmounts1 = vector<double>{1000, 2000};
//    vector<string> lenders1 = vector<string>{"lenderA1", "lenderA2"};
//    vector<double> lenderAmounts2 = vector<double>{100, 200};
//    vector<string> lenders2 = vector<string>{"lenderA1", "lenderB2"};
//    auto facility = new Facility("2021-01-01", "2021-12-31", lenderAmounts1, "USD", lenders1);
//    auto facility2 = new Facility("2021-01-01", "2021-12-31", lenderAmounts2, "EUR", lenders2);
//    auto portfolio2 = new Portfolio("lenderA1", vector<Facility*>{facility, facility2});
//    cout << "Portfolio 2 lender: " << portfolio2->getLender() << endl;
//    cout << "Portfolio 2 facilities: ";
//    for (Facility* aFacility : portfolio2->getFacilities()) {
//        cout << "(" << aFacility->getCurrency() << ") ";
//    }
//    cout << endl;
//    cout << "Portfolio 2 all currency interests: ";
//    for (double interest : portfolio2->getAllCurrencyInterests()) {
//        cout << interest << ", ";
//    }
//    cout << endl;
//
//    // test getAccountByCurrency
//    cout << "Portfolio 2 account by currency: " << portfolio2->getAccountByCurrency("USD")->getCurrency() << endl;
//    cout << "Portfolio 2 account by currency: " << portfolio2->getAccountByCurrency("RMB")->getCurrency() << endl;
//
//    // test addFacility
//    auto portfolio1 = new Portfolio("lenderA1");
//    cout << "Before: " << portfolio1->getAccountByCurrency("USD")->getBalance() << endl;
//    portfolio1->addFacility(facility);
//    cout << "After: " << portfolio1->getAccountByCurrency("USD")->getBalance() << endl;
//
//    // test recalculateCurrencyInterest
//    cout << "Before: " << portfolio1->getAccountByCurrency("EUR")->getBalance() << endl;
//    portfolio1->addFacility(facility2);
//    cout << "After: " << portfolio1->getAccountByCurrency("EUR")->getBalance() << endl;
//    double recalculatedInterest = portfolio1->recalculateCurrencyInterest("EUR");
//    cout << "Recalculated interest: " << recalculatedInterest << endl;
//
//    return EXIT_SUCCESS;
//}