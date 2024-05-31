#include <iostream>
#include <utility>
#include "Borrower.h"
#include "utils/Utils.h"

using namespace std;
// Constructor
Borrower::Borrower(string name) : name(std::move(name)) {
}

// Getters
string Borrower::getName() const {
    return name;
}

void Borrower::display() {
    cout << "[Borrower] " << this->name << endl;
}

void Borrower::serialize(ostream& out) const {
    out << "Borrower: {" << endl;
    out << "    name: " << endl;
    out << "        " << name << endl;
    out << "}" << endl;
}

Borrower* Borrower::deserialize(istream& in) {
    string line, nm;

    getline(in, line);
    if (line != "Borrower: {") {
//        cerr << "Expected 'Borrower: {' but got: \"" << line  << "\"" << endl;
        return nullptr;
    }

    // Read name
    getline(in, line);  // Skip "name:"
    getline(in, nm);    // Read name
    // trim white spaces
    nm = Utils::trim(nm);
    in >> line;  // Skip "}"

    if (line != "}") {
        cerr << "[Borrower] Expected '}' but got: \"" << line << "\"" << endl;
        return nullptr;
    }

    return new Borrower(nm);
}