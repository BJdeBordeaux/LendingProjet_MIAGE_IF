#include <utility>
#include <vector>
#include <iostream>
#include "Account.h"
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


//int main() {
//    // what is store in a vector of class, is it the object or the reference to the object?
//    auto account1 = new Account("USD", 1000);
//    vector<Account*> currencyAccounts;
//    currencyAccounts.push_back(account1);
//    cout << "Account 1 balance: " << currencyAccounts[0]->getBalance() << endl;
//    account1->deposit(1000);
//    cout << "Account 1 balance after deposit: " << currencyAccounts[0]->getBalance() << endl;
//    return 0;
//}


