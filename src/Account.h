#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

class Account {
public:
    Account(const std::string& currency, double amount);

    void deposit(double amount);
    void withdraw(double amount);
    double getBalance() const;

private:
    std::string currency;
    double amount;
};

#endif // ACCOUNT_H
