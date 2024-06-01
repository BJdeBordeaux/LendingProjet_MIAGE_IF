#include "Part.h"
#include "utils/Utils.h"

#include <utility>

// Constructor
Part::Part(string borrower, double repaidAmount): borrower(std::move(borrower)), repaidAmount(repaidAmount) {}

// Getters
double Part::getRepaidAmount() const {
    return repaidAmount;
}

string Part::getBorrower() const {
    return borrower;
}

void Part::serialize(ostream& out) const {
    out << "Part: {" << endl;
    out << "    borrowers: " << endl;
    out << "        " << borrower << endl;
    out << "    repaidAmount: " << repaidAmount << endl;
    out << "}" << endl;
}

Part* Part::deserialize(istream& in) {
    string line, brw;
    double repAmt;

    getline(in, line);
    if (line != "Part: {") {
        cerr << "Expected 'Part: {' but got: \"" << line  << "\"" << endl;
        return nullptr;
    }

    // Read borrowers
    getline(in, line);  // Skip "borrowers:"
    getline(in, brw);   // Read borrowers
    // trim white spaces
    brw = Utils::trim(brw);
    in >> line >> repAmt;  // Read repaidAmount
    in >> line;  // Skip "}"

    if (line != "}") {
        cerr << "[Part] Expected '}' but got: \"" << line << "\"" << endl;
        return nullptr;
    }

    return new Part(brw, repAmt);
}

void Part::display() {
    cout << "[Part] " << this->borrower << " " << this->repaidAmount << endl;
}

