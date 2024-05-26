#include "Account.h"

Account::Account(const std::string& currency, double amount)
        : currency(currency), amount(amount) {}

void Account::deposit(double amount) {
    this->amount += amount;
}

void Account::withdraw(double amount) {
    if (this->amount >= amount) {
        this->amount -= amount;
    } else {
        // Handle insufficient funds
    }
}

double Account::getBalance() const {
    return this->amount;
}
