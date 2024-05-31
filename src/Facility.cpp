#include <iostream>
#include <utility>
#include "utils/Utils.h"
#include "Facility.h"
#include "Part.h"
using namespace std;

double dailyInterestRate = 0.0003;

// Constructor
Facility::Facility(string  startDate, string  endDate, vector<double> lenderAmounts, string  currency,
                   vector<string> lenders)
        : startDate(std::move(startDate)), endDate(std::move(endDate)), lenderAmounts(std::move(lenderAmounts)), currency(std::move(currency)), lenders(std::move(lenders)) {}

// Getters
string Facility::getStartDate(){
    return startDate;
}

string Facility::getEndDate(){
    return endDate;
}

string Facility::getCurrency(){
    return currency;
}

vector<string> Facility::getLenders() {
    return lenders;
}

vector<double> Facility::getLenderAmounts() {
    return lenderAmounts;
}

vector<Part*> Facility::getParts() {
    return this->parts;
}

// Other methods
Part* Facility::addPart(Part* part) {
    this->parts.push_back(part);
    return part;
}

double Facility::calculateInterest(const string& lender) {
    // see index of lender, if nout found, return 0
    int index = -1;
    for (int i = 0; i < lenders.size(); i++) {
        if (lenders[i] == lender) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        return -1;
    }

    // calculer le total des interets, puis distribuer les interets aux parties
    double totalInterest = 0;
    // check if today is after end date
    int dateDiff = Utils::dateDifferenceTodayMinusADate(endDate);
    if (dateDiff > 0) {
        // calculate interest : lenderAmount * dailyInterestRate * dateDiff
        return lenderAmounts[index] * dailyInterestRate * dateDiff;
    } else {
        // not due yet
        return -1;
    }

}

//double Facility::calculateRemainingInterestAmount(){
//    double totalRepaid = 0;
//    for (const auto& part : parts) {
//        totalRepaid += part.getRepaidAmount();
//    }
//    return lenderAmount - totalRepaid;
//}

double Facility::getTotalAmount() {
    double totalAmount = 0;
    for (double lenderAmount : this->getLenderAmounts()) {
        totalAmount += lenderAmount;
    }
    return totalAmount;
}

double Facility::calculateTotalInterest() {
    double totalInterest = 0;
    int dateDiff = Utils::dateDifferenceTodayMinusADate(endDate);
    if (dateDiff > 0) {
        // calculate interest : lenderAmount * dailyInterestRate * dateDiff
        return this->getTotalAmount() * dailyInterestRate * dateDiff;
    } else {
        // not due yet
        return 0;
    }
}

double Facility::calculateRemainingInterestAmount() {
    double totalRepaid = 0;
    for (const auto& part : parts) {
        totalRepaid += part->getRepaidAmount();
    }
    double remainingInterest = this->calculateTotalInterest() - totalRepaid;
    if (remainingInterest < 0) {
        return 0;
    } else {
        return remainingInterest;
    }
}

void Facility::display(bool displayLenders) {
    cout << "[Facility] " << this->startDate << " => " << this->endDate
        << " total amount: " << this->getTotalAmount()
        << ", remaining interest amount: " << this->calculateRemainingInterestAmount()
        << " (" << this->currency << ")" << endl;
    if (displayLenders) {
        cout << "\tLenders: ";
        for (int i = 0; i < lenders.size() - 1; i++) {
            cout << lenders[i] << " (" << lenderAmounts[i] << ") ";
        }
        cout << lenders[lenders.size() - 1] << " (" << lenderAmounts[lenders.size() - 1] << ")";
        cout << endl;

    }
}

// Facility serialization and deserialization implementation

void Facility::serialize(ostream& out) const {
    out << "Facility: {" << endl;
    out << "    startDate: " << endl;
    out << "        " << startDate << endl;
    out << "    endDate: " << endl;
    out << "        " << endDate << endl;
    out << "    currency: " << endl;
    out << "        " << currency << endl;
    out << "    lenderAmounts: [" << endl;
    for (double amt : lenderAmounts) {
        out << "        " << amt << endl;
    }
    out << "    ]" << endl;
    out << "    lenders: [" << endl;
    for (const string& lender : lenders) {
        out << "        " << lender << endl;
    }
    out << "    ]" << endl;
    out << "    parts: [" << endl;
    for (Part* part : parts) {
        part->serialize(out);
    }
    out << "    ]" << endl;
    out << "}" << endl;
}

Facility* Facility::deserialize(istream& in) {
    string line, stDate, enDate, curr;
    vector<double> lendAmts;
    vector<string> lendrs;
    vector<Part*> prts;

    getline(in, line); // Skip "Facility: {" (already read in the caller function
    if (line != "Facility: {") {
        cerr << "Expected 'Facility: {' but got: \"" << line  << "\"" << endl;
        return nullptr;
    }

    // Read startDate
    in >> line;  // Skip "startDate:"
    in >> stDate;  // Read startDate
    // trim white spaces
    stDate = Utils::trim(stDate);

    // Read endDate
    in >> line;  // Skip "endDate:"
    in >> enDate;  // Read endDate
    // trim white spaces
    enDate = Utils::trim(enDate);

    // Read currency
    in >> line;  // Skip "currency:"
    in >> curr;  // Read currency
    // trim white spaces
    curr = Utils::trim(curr);

    getline(in, line);  // Skip newline character
    getline(in, line);  // Skip "lenderAmounts: ["
    double amt;
    in >> amt;
    do {
        lendAmts.push_back(amt);
        in >> line;
        if (line == "]") break;
        amt = stod(line);
    } while (true);

    // Read lenders
    in >> line; in >> line;  // Skip "lenders: ["
    string lender;
    getline(in, lender); // Skip newline character
    while (getline(in, lender)) {
        lender = Utils::trim(lender);
        if (lender == "]") break;
        lendrs.push_back(lender);
    }

    // Read parts
    getline(in, line);
    if (line == "") {
        getline(in, line);  // Skip "parts: ["
    }
//    in >> line; in >> line;;  // Skip "parts: ["
    while (getline(in, line) && line != "    ]") {
        if (line == "Part: {") {
            stringstream ss;
            ss << line << endl;
            while (getline(in, line) && line != "}") {
                ss << line << endl;
            }
            ss << line;
            Part* part = Part::deserialize(ss);
            if (part) prts.push_back(part);
        }
    }

    cout << "[Facility] line: " << line << endl;

    in >> line;  // Skip "}"

    if (line != "}") {
        cerr << "[Facility] Expected '}' but got: \"" << line << "\"" << endl;
        return nullptr;
    }

    auto facility = new Facility(stDate, enDate, lendAmts, curr, lendrs);
    for (Part* part : prts) {
        facility->addPart(part);
    }

    return facility;
}