#include <iostream>
#include "Lender.h"
#include "Portfolio.h"
#include "utils/Utils.h"

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

void Lender::display() {
    cout << "[Lender] " << this->name << endl;
}

void Lender::serialize(ostream& out) const {
    out << "Lender: {" << endl;
    out << "    name: " << endl;
    out << "        " << name << endl;
    out << "    portfolio: {" << endl;
    if (portfolio) {
        portfolio->serialize(out);
    }
    out << "    }" << endl;
    out << "}" << endl;
}

Lender* Lender::deserialize(istream& in) {
    string line, nm;
    Portfolio* port = nullptr;

    getline(in, line);
    if (line != "Lender: {") {
//        cerr << "Expected 'Lender: {' but got: \"" << line << "\"" << endl;
        return nullptr;
    }

    // Read name
    getline(in, line);  // Skip "name:"
    getline(in, nm);    // Read name
    nm = Utils::trim(nm);

    // Read portfolio
    getline(in, line);  // Skip "portfolio: {"
    if (Utils::trim(line) == "portfolio: {") {
        stringstream ss;
        while (getline(in, line) && line != "    }") {
            ss << line << endl;
        }
        ss << "}";
        port = Portfolio::deserialize(ss);
    }

    getline(in, line);  // Skip "}"

    if (line != "}") {
        cerr << "Expected '}' but got: \"" << line << "\"" << endl;
        // output the rest of file
        while (getline(in, line)) {
            cerr << line << endl;
        }
        return nullptr;
    }

    auto lender = new Lender(nm);
    lender->portfolio = port;

    return lender;
}