#ifndef BORROWER_H
#define BORROWER_H

#include <string>
#include "Portfolio.h"
#include "Account.h"
#include "Deal.h"

using namespace std;

class Borrower {
public:
    // Constructor
    explicit Borrower(string  name);

    // Getters
    string getName() const;

    // Other methods
    void display();

    // Serialization
    void serialize(ostream& out) const;
    static Borrower* deserialize(istream& in);

private:
    string name;
};

#endif // BORROWER_H

