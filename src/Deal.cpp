#include <utility>
#include <iostream>
#include "Deal.h"
#include "Facility.h"
#include "utils/Utils.h"
#include "Borrower.h"

using namespace std;

// Constructor
Deal::Deal(string contractNumber, string agent, const vector<string>& borrowers, vector<Facility*> facilities)
    : contractNumber(std::move(contractNumber)), agent(std::move(agent)), status("closed"){

    // init
    int currencyIndex = -1;
    string start_date_str = facilities[0]->getStartDate();
    string end_date_str = facilities[0]->getEndDate();

    // add borrowers
    for (const auto& borrower : borrowers) {
        this->addBorrower(borrower);
    }

    // add facilities
    for (Facility* facility : facilities) {
        this->addFacility(facility);
    }

    // check facilities information
    for (Facility* facility : facilities) {

        // find the earliest start date as start_date_str and latest end date as end_date_str
        string facility_start_date = facility->getStartDate();
        string facility_end_date = facility->getEndDate();
        if (Utils::dateDifference(start_date_str, facility_start_date) < 0) {
            start_date_str = facility_start_date;
        }
        if (Utils::dateDifference(end_date_str, facility_end_date) > 0) {
            end_date_str = facility_end_date;
        }

        // add lenders to pool
        for (const auto& lender : facility->getLenders()) {
            // if lender not in pool, add it
            bool found = false;
            for (const auto& poolLender : pool) {
                if (lender == poolLender) {
                    found = true;
                    break;
                }
            }
            if (!found && (lender != this->getAgent())) {
                this->pool.push_back(lender);
            }
        }

        // add currency to currencies and its amount to projectAmounts
        string facilityCurrency = facility->getCurrency();
        currencyIndex = -1;
        for (int i = 0; i < currencies.size(); i++) {
            if (facility->getCurrency() == currencies.at(i)) {
                currencyIndex = i;
            }
        }
        if (currencyIndex == -1) {
            this->currencies.push_back(facilityCurrency);
            this->projectAmounts.push_back(facility->getTotalAmount());
        } else {
            this->projectAmounts.at(currencyIndex) += facility->getTotalAmount();
        }

    }

    this->startDate = start_date_str;
    this->endDate = end_date_str;
}

// Getters
string Deal::getContractNumber() const {
    return contractNumber;
}

string Deal::getAgent() const {
    return agent;
}

vector<string> Deal::getPool() const {
    return pool;
}

vector<string> Deal::getBorrowers() const {
    return borrowers;
}

vector<double> Deal::getProjectAmounts() const {
    return projectAmounts;
}

vector<string> Deal::getCurrencies() const {
    return currencies;
}

string Deal::getStartDate() const {
    return startDate;
}

string Deal::getEndDate() const {
    return endDate;
}

string Deal::getStatus() const {
    return status;
}

vector<Facility*> Deal::getFacilities() {
    return facilities;
}

// Other methods
Facility* Deal::addFacility(Facility* facility) {
    facilities.push_back(facility);
    return facility;
}

string Deal::addBorrower(string borrower) {
    borrowers.push_back(borrower);
    return borrower;
}

void Deal::display(bool displayFacilities) {
    cout << "[Deal] "<< contractNumber <<
        " (" << startDate << " => " << endDate << ") status: " << status << endl;
    cout << "\tCurrencies: ";
    for (int i = 0; i < currencies.size()-1; i++) {
        cout << projectAmounts[i] << " (" << currencies[i] << "), ";
    }
    cout << projectAmounts[currencies.size()-1] << " (" << currencies[currencies.size()-1] << ")";
    cout << endl;

    cout << "\tBorrower: ";
    const vector<string> &brs = this->getBorrowers();
    for (int i = 0; i < brs.size() - 1; i++) {
        cout << brs[i] << ", ";
    }
    cout << borrowers[borrowers.size()-1] << endl;
    cout << "\tAgent: " << agent << endl;
    cout << "\tPool: ";
    const vector<string> &pls = this->getPool();
    for (int i = 0; i < pls.size() - 1; i++) {
        cout << pls[i] << ", ";
    }
    cout << pls[pls.size() - 1] << endl;
    cout << endl;
    if (displayFacilities) {
        for (const auto& facility : facilities) {
            cout << "\t";
            facility->display(true);
        }
    }
}

void Deal::serialize(ostream& out) const {
    out << "Deal: {" << endl;
    out << "    contractNumber: " << endl;
    out << "        " << contractNumber << endl;
    out << "    agent: " << endl;
    out << "        " << agent << endl;
//    out << "    borrowers: " << endl;
//    out << "        ";
//    for (const auto& borrower : borrowers) {
//        out << borrower << ", ";
//    }
//    out << endl;
    out << "    pool: " << endl;
    out << "        ";
    for (const auto& lender : pool) {
        out << lender << ", ";
    }
    out << endl;
    out << "    status: " << endl;
    out << "        " << status << endl;
    out << "    startDate: " << endl;
    out << "        " << startDate << endl;
    out << "    endDate: " << endl;
    out << "        " << endDate << endl;
    out << "    facilities: [" << endl;
    for (Facility* fac : facilities) {
        fac->serialize(out);
    }
    out << "    ]" << endl;
    out << "}" << endl;
}

Deal* Deal::deserialize(istream& in) {
    string line, cn, ag, brw, st, sDate, eDate;
    vector<Facility*> facs;

    getline(in, line);
    if (line != "Deal: {") {
        cerr << "Expected 'Deal: {' but got: \"" << line  << "\"" << endl;
        // print the rest
        while (getline(in, line)) {
            cerr << line << endl;
        }
        return nullptr;
    }

    // Read contractNumber
    getline(in, line);  // Skip "contractNumber:"
    getline(in, cn);    // Read contractNumber
    cn = Utils::trim(cn);

    // Read agent
    getline(in, line);  // Skip "agent:"
    getline(in, ag);    // Read agent
    ag = Utils::trim(ag);

//    // Read borrowers
//    getline(in, line);  // Skip "borrowers:"
//    getline(in, brw);   // Read borrowers
//    brw = Utils::trim(brw);

    // Read status
    getline(in, line);  // Skip "status:"
    getline(in, st);    // Read status
    st = Utils::trim(st);

    // Read startDate
    getline(in, line);  // Skip "startDate:"
    getline(in, sDate); // Read startDate
    sDate = Utils::trim(sDate);

    // Read endDate
    getline(in, line);  // Skip "endDate:"
    getline(in, eDate); // Read endDate
    eDate = Utils::trim(eDate);

    // Read facilities
    getline(in, line);  // Skip "facilities: ["
    while (getline(in, line) && Utils::trim(line) != "]") {
        if (line == "Facility: {") {
            stringstream ss;
            ss << line << endl;
            while (getline(in, line) && line != "}") {
                ss << line << endl;
            }
            ss << line;
            Facility* fac = Facility::deserialize(ss);
            if (fac) {
                facs.push_back(fac);
            }
        }
    }

    getline(in, line);  // Skip "}"

    if (line != "}") {
        cerr << "[Deal] Expected '}' but got: \"" << line << "\"" << endl;
        return nullptr;
    }

    return new Deal(cn, ag, {"Total Energie"}, facs);
}