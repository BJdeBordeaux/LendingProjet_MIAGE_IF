#include "Facility.h"
#include <iostream>
#include <utility>
#include "utils/Utils.h"
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

vector<Part>& Facility::getParts() {
    return parts;
}

// Other methods
//void Facility::addPart(const Part& part) {
//    parts.push_back(part);
//}

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

//double Facility::getRemainingAmount(){
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

//int main(){
//    // test all methods
//    vector<double> lenderAmounts = vector<double>{1000, 2000};
//    vector<string> vector1 = vector<string>{"lender1", "lender2"};
//    auto facility = new Facility("2021-01-01", "2021-12-31", lenderAmounts, "USD", vector1);
//    cout << "Facility start date: " << facility->getStartDate() << endl;
//    cout << "Facility end date: " << facility->getEndDate() << endl;
//    cout << "Facility currency: " << facility->getCurrency() << endl;
//    cout << "Facility lenders: ";
//    for (const string& lender : facility->getLenders()) {
//        cout << lender << " ";
//    }
//    cout << endl;
//
//    cout << "Facility lender amounts: ";
//    for (double lenderAmount : facility->getLenderAmounts()) {
//        cout << lenderAmount << " ";
//    }
//    cout << endl;
//
//    cout << "Facility total amount: " << facility->getTotalAmount() << endl;
//
//    cout << "Facility interest for lender1: " << facility->calculateInterest("lender1") << endl;
//    cout << "Facility interest for lender2: " << facility->calculateInterest("lender2") << endl;
//    return 0;
//}
