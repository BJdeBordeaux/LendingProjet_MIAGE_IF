#include "Portfolio.h"
#include "utils/Utils.h"
#include <iostream>
#include <utility>
#include <sstream>

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

vector<Account *> Portfolio::getCurrencyAccounts() const {
    return currencyAccounts;
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

vector<string> Portfolio::getAllCurrencies() const {
    auto allCurrencies = vector<string>{};
    for (Account* account : currencyAccounts) {
        allCurrencies.push_back(account->getCurrency());
    }
    return allCurrencies;
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

    // Update the currencies interest
    for(Account* accountToUpdate: currencyAccounts) {
        if(accountToUpdate->getCurrency() == currency) {
            accountToUpdate->setBalance(recalculatedCurrencyInterest);
        }
    }

    return recalculatedCurrencyInterest;
}

void Portfolio::display() {
    cout << "[Portfolio] lender: " << lender << endl;
    auto allCurrencyInterests = this->getAllCurrencyInterests();
    auto allCurrencies = this->getAllCurrencies();
    for (int i = 0; i < allCurrencies.size(); i++) {
        cout << "\t" << allCurrencies[i] << ": " << allCurrencyInterests[i] << endl;
    }
}

//void Portfolio::serialize(ostream& out) const {
//    out << "Portfolio: {" << endl;
//    out << "    lender: " << endl;
//    out << "        " << lender << endl;
//    out << "    currencyAccounts: [" << endl;
//    for (Account* acc : currencyAccounts) {
//        acc->serialize(out);
//    }
//    out << "    ]" << endl;
//    out << "    facilities: [" << endl;
//    for (Facility* fac : facilities) {
//        fac->serialize(out);
//    }
//    out << "    ]" << endl;
//    out << "}" << endl;
//}
//
//Portfolio* Portfolio::deserialize(istream& in) {
//    string line, lndr;
//    vector<Account*> accs;
//    vector<Facility*> facs;
//
//    getline(in, line);
//    if (line != "Portfolio: {") {
//        cerr << "Expected 'Portfolio: {' but got: \"" << line  << "\"" << endl;
//        return nullptr;
//    }
//
//    // Read lender
//    getline(in, line);  // Skip "lender:"
//    getline(in, lndr);  // Read lender
//    lndr = Utils::trim(lndr);
//
//    // Read currencyAccounts
//    getline(in, line);  // Skip "currencyAccounts: ["
//    while (getline(in, line) && Utils::trim(line) != "]") {
//        if (line == "Account: {") {
//            stringstream ss;
//            ss << line << endl;
//            while (getline(in, line) && line != "}") {
//                ss << line << endl;
//            }
//            ss << line;
//            Account* acc = Account::deserialize(ss);
//            if (acc) accs.push_back(acc);
//        }
//    }
//
//    // Read facilities
//    getline(in, line);  // Skip "facilities: ["
//    while (getline(in, line) && Utils::trim(line) != "]") {
//        if (line == "Facility: {") {
//            stringstream ss;
//            ss << line << endl;
//            while (getline(in, line) && line != "}") {
//                ss << line << endl;
//            }
//            ss << line;
//            Facility* fac = Facility::deserialize(ss);
//            if (fac) facs.push_back(fac);
//        }
//    }
//
//    getline(in, line);  // Skip "}"
//
//    if (line != "}") {
//        cerr << "[Portfolio] Expected '}' but got: \"" << line << "\"" << endl;
//        // output the rest of file
//        while (getline(in, line)) {
//            cerr << line << endl;
//        }
//        return nullptr;
//    }
//
//    auto portfolio = new Portfolio(lndr);
//    portfolio->currencyAccounts = accs;
//    for (Facility* fac : facs) {
//        portfolio->addFacility(fac);
//    }
//
//    return portfolio;
//}

void Portfolio::serialize(ostream& out) const {
    out << "Portfolio: {" << endl;
    out << "    lender: " << endl;
    out << "        " << lender << endl;
    out << "    currencyAccounts: [" << endl;
    for (Account* acc : currencyAccounts) {
        acc->serialize(out);
    }
    out << "    ]" << endl;
    out << "}" << endl;
}

Portfolio* Portfolio::deserialize(istream& in) {
    string line, lndr;
    vector<Account*> accs;

    getline(in, line);
    if (line != "Portfolio: {") {
        cerr << "Expected 'Portfolio: {' but got: \"" << line  << "\"" << endl;
        return nullptr;
    }

    // Read lender
    getline(in, line);  // Skip "lender:"
    getline(in, lndr);  // Read lender
    lndr = Utils::trim(lndr);

    // Read currencyAccounts
    getline(in, line);  // Skip "currencyAccounts: ["
    while (getline(in, line) && Utils::trim(line) != "]") {
        if (line == "Account: {") {
            stringstream ss;
            ss << line << endl;
            while (getline(in, line) && line != "}") {
                ss << line << endl;
            }
            ss << line;
            Account* acc = Account::deserialize(ss);
            if (acc) accs.push_back(acc);
        }
    }

    getline(in, line);  // Skip "}"

    if (line != "}") {
        cerr << "[Portfolio] Expected '}' but got: \"" << line << "\"" << endl;
        // output the rest of file
        while (getline(in, line)) {
            cerr << line << endl;
        }
        return nullptr;
    }

    auto portfolio = new Portfolio(lndr);
    portfolio->currencyAccounts = accs;

    return portfolio;
}

