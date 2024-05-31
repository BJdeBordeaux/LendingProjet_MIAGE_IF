#include <utility>
#include <vector>
#include <iostream>
#include <iomanip>
#include "Account.h"
#include "utils/Utils.h"
using namespace std;
Account::Account(string currency, double amount)
        : currency(std::move(currency)), amount(amount) {}
Account::Account(string currency): currency(std::move(currency)), amount(0) {}

double Account::deposit(double depositAmount) {
    this->amount += depositAmount;
    return this->amount;
}

double Account::withdraw(double withdrawAmount) {
    if (this->amount >= withdrawAmount) {
        this->amount -= withdrawAmount;
        return amount;
    } else {
        return 0;
    }
}



double Account::getBalance() const {
    return this->amount;
}

string Account::getCurrency() {
    return this->currency;
}

void Account::setBalance(double balance) {
    this->amount = balance;
}

void Account::serialize(ostream& out) const {
    out << "Account: {" << endl;
    out << "    currency: " <<endl;
    out << "        " << currency << endl;
    out << "    amount: " << amount << endl;
    out << "}" << endl;
}

Account* Account::deserialize(istream& in) {
    string line, curr;
    double amt;

    getline(in, line);
    if (line != "Account: {") {
        cerr << "Expected 'Account: {' but got: \"" << line  << "\"" << endl;
        return nullptr;
    }

    // Read currency
    getline(in, line);  // Skip "currency:"
    getline(in, curr);  // Read currency
    // trim white spaces
    curr = Utils::trim(curr);
    in >> line >> amt;  // Read amount
    in >> line;  // Skip "}"

    if (line != "}") {
        cerr << "[Account] Expected '}' but got: \"" << line << "\"" << endl;
        return nullptr;
    }

    return new Account(curr, amt);
}

void Account::display() {
    cout << fixed << setprecision(2) << "[Account] " << this->amount << " " << this->currency << endl;
}


