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

    // Serialization
    void serialize(ostream& out) const;
    static Account* deserialize(istream& in);

    // Other methods
    double deposit(double amount);
    double withdraw(double amount);
    void display();



private:
    string currency;
    double amount;
};

#endif // ACCOUNT_H
