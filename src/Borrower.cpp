#include <iostream>
#include <utility>
#include "Borrower.h"
#include "Portfolio.h"

using namespace std;
// Constructor
Borrower::Borrower(string name) : name(std::move(name)) {
}

// Getters
string Borrower::getName() const {
    return name;
}


//int main() {
//    // test all method
//    Borrower borrower("Borrower");
//    cout << borrower.getName() << endl;
//}