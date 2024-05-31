#ifndef PART_H
#define PART_H
#include <iostream>
using namespace std;

class Part {
public:
    // Constructor
    Part(string borrower, double repaidAmount);

    // Getters
    double getRepaidAmount() const;
    string getBorrower() const;

    // Other methods
    void display();

    // Serialization
    void serialize(ostream& out) const;
    static Part* deserialize(istream& in);

private:
    double repaidAmount;
    string borrower;
};

#endif // PART_H
