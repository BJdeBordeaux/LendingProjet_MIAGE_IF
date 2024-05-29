#include <utility>
#include <iostream>
#include "Deal.h"
#include "Facility.h"
#include "Portfolio.h"
#include "utils/Utils.h"

using namespace std;

// Constructor
Deal::Deal(string  contractNumber, string  agent, const vector<string>& pool,
           string  borrower, double projectAmount, string  currency,
           string  startDate, string  endDate, string  status)
        : contractNumber(std::move(contractNumber)), agent(std::move(agent)), pool(pool),
        borrower(std::move(borrower)), projectAmount(projectAmount), currency(std::move(currency)),
        startDate(std::move(startDate)), endDate(std::move(endDate)), status(std::move(status)) {}

Deal::Deal(string contractNumber, string agent, const vector<string> &pool, string borrower, double projectAmount,
           string currency, string startDate, string endDate)
           : contractNumber(std::move(contractNumber)), agent(std::move(agent)), pool(pool),
           borrower(std::move(borrower)), projectAmount(projectAmount),currency(std::move(currency)),
           startDate(std::move(startDate)), endDate(std::move(endDate)), status("closed"){}

Deal::Deal(string contractNumber, string agent, string borrower, string currency, vector<Facility*> facilities)
    : contractNumber(std::move(contractNumber)), agent(std::move(agent)),
    borrower(std::move(borrower)),currency(std::move(currency)), status("closed"){
    // add facilities
    for (Facility* facility : facilities) {
        this->addFacility(facility);
    }
    // find earliest start date as start_date and latest end date as end_date
    string start_date = facilities[0]->getStartDate();
    string end_date = facilities[0]->getEndDate();
    // convert string to date

    for (Facility* facility : facilities) {
        if (facility->getStartDate() < start_date) {
            start_date = facility->getStartDate();
        }
        if (facility->getEndDate() > end_date) {
            end_date = facility->getEndDate();
        }
    }

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

string Deal::getBorrower() const {
    return borrower;
}

double Deal::getProjectAmount() const {
    return projectAmount;
}

string Deal::getCurrency() const {
    return currency;
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

double Deal::calculateTotalAmount() const {
    double totalAmount = 0;
    for (const auto facility : facilities) {
        totalAmount += facility->getTotalAmount();
    }
    return totalAmount;
}


int main(){

    // prepare data
    vector<double> lenderAmounts1 = vector<double>{1000, 2000};
    vector<string> lenders1 = vector<string>{"lenderA1", "lenderA2"};
    vector<double> lenderAmounts2 = vector<double>{100, 200};
    vector<string> lenders2 = vector<string>{"lenderA1", "lenderB2"};
    auto facility = new Facility("2021-01-01", "2021-12-31", lenderAmounts1, "USD", lenders1);
    auto facility2 = new Facility("2021-01-01", "2021-12-31", lenderAmounts2, "EUR", lenders2);

    // test all methods
    auto deal = new Deal("S0001", "LenderA1", vector<string>{"LenderA2", "LenderB2"}, "Borrower1", 1000, "USD", "2021-01-01", "2021-12-31");
    deal->addFacility(facility);
    deal->addFacility(facility2);
    cout << "Deal contract number: " << deal->getContractNumber() << endl;
    cout << "Deal agent: " << deal->getAgent() << endl;
    cout << "Deal pool: ";
    for (const auto& pool : deal->getPool()) {
        cout << pool << ", ";
    }
    cout << endl;
    cout << "Deal borrower: " << deal->getBorrower() << endl;
    cout << "Deal project amount: " << deal->getProjectAmount() << endl;
    cout << "Deal currency: " << deal->getCurrency() << endl;
    cout << "Deal start date: " << deal->getStartDate() << endl;
    cout << "Deal end date: " << deal->getEndDate() << endl;
    cout << "Deal status: " << deal->getStatus() << endl;
    cout << "Deal total amount: " << deal->calculateTotalAmount() << endl;
    cout << "Deal facilities: ";
    for (const auto& facility : deal->getFacilities()) {
        cout << "(" << facility->getCurrency() << ") ";
    }
    cout << endl;

    return EXIT_SUCCESS;
}

