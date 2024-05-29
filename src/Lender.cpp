#include <iostream>
#include "Lender.h"
#include "Portfolio.h"
using namespace std;

// Constructor
Lender::Lender(const string &name) : name(name) {
    portfolio = new Portfolio(name);
}

string Lender::getName() const {
    return name;
}

Portfolio *Lender::getPortfolio() {
    return portfolio;
}

//int main() {
//    auto myLender = new Lender("Lender1");
//    cout << myLender->getName() << endl;
//    cout << myLender->getPortfolio()->getLender() << endl;
//}
