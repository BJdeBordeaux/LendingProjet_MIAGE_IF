#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
using namespace std;
class Account {
public:
    Account(string  currency, double amount);
    explicit Account(string  currency);

    // getters and setters
    string getCurrency();
    double getBalance() const;
    void setBalance(double balance);

    // Other methods
    double deposit(double amount);
    double withdraw(double amount);

private:
    string currency;
    double amount;
};

#endif // ACCOUNT_H
