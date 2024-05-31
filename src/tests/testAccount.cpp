#include "Account.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>

int main() {
    // what is store in a vector of class, is it the object or the reference to the object?
    auto account1 = new Account("USD", 1000);
    vector<Account*> currencyAccounts;
    currencyAccounts.push_back(account1);
    cout << "Account 1 balance: " << currencyAccounts[0]->getBalance() << endl;
    account1->deposit(1000);
    cout << "Account 1 balance after deposit: " << currencyAccounts[0]->getBalance() << endl;
    account1->deposit(1.345);
    account1->display();

    // test serialization
    // Serialize the account object to a file
    ofstream outFile("accountSerialization.txt");
    if (outFile.is_open()) {
        account1->serialize(outFile);
        outFile.close();
        cout << "Account saved to file." << endl;
    } else {
        cerr << "Unable to open file for writing." << endl;
    }

    // Deserialize the account object from the file
    ifstream inFile("accountSerialization.txt");
    if (inFile.is_open()) {
        Account* restoredAccount = Account::deserialize(inFile);
        inFile.close();
        if (restoredAccount != nullptr) {
            cout << "Account restored from file:" << endl;
            restoredAccount->display();
            delete restoredAccount; // Don't forget to free the memory
        } else {
            cerr << "Failed to restore account from file." << endl;
        }
    } else {
        cerr << "Unable to open file for reading." << endl;
    }
    return 0;
}