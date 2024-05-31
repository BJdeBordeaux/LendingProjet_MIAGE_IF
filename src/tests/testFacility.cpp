#include <iostream>
#include <fstream>
#include <sstream>
#include "Facility.h"
using namespace std;

int main(){
    // test all methods
    vector<double> lenderAmounts = vector<double>{1000, 2000};
    vector<string> vector1 = vector<string>{"lender1", "lender2"};
    auto facility = new Facility("2021-01-01", "2021-12-31", lenderAmounts, "USD", vector1);
    cout << "Facility start date: " << facility->getStartDate() << endl;
    cout << "Facility end date: " << facility->getEndDate() << endl;
    cout << "Facility currencies: " << facility->getCurrency() << endl;
    cout << "Facility lenders: ";
    for (const string& lender : facility->getLenders()) {
        cout << lender << " ";
    }
    cout << endl;

    cout << "Facility lender amounts: ";
    for (double lenderAmount : facility->getLenderAmounts()) {
        cout << lenderAmount << " ";
    }
    cout << endl;

    cout << "Facility total amount: " << facility->getTotalAmount() << endl;

    cout << "Facility interest for lender1: " << facility->calculateInterest("lender1") << endl;
    cout << "Facility interest for lender2: " << facility->calculateInterest("lender2") << endl;
    auto part1 = new Part("borrower1", 1);
    auto part2 = new Part("borrower2", 2);
    facility->display();
    facility->addPart(part1);
    facility->display(true);
    facility->addPart(part2);
    facility->display(true);

    // test serialization
    cout << "Serialization and deserialization" << endl;
    ofstream out("facilitySerialization.txt");
    if (out.is_open()) {
        facility->serialize(out);
        out.close();
    } else {
        cout << "Unable to open file" << endl;
    }

    ifstream in("facilitySerialization.txt");
    if (in.is_open()) {
        auto facility2 = Facility::deserialize(in);
        facility2->display(true);
        in.close();
    } else {
        cout << "Unable to open file" << endl;
    }

    string f_to_restore = "Facility: {\n"
                          "    startDate: \n"
                          "        2023-01-01\n"
                          "    endDate: \n"
                          "        2024-01-01\n"
                          "    currency: \n"
                          "        USD\n"
                          "    lenderAmounts: [\n"
                          "        10000\n"
                          "    ]\n"
                          "    lenders: [\n"
                          "        Term Loan\n"
                          "    ]\n"
                          "    parts: [\n"
                          "Part: {\n"
                          "    borrower: \n"
                          "        Term Loan\n"
                          "    repaidAmount: 1000\n"
                          "}\n"
                          "    ]\n"
                          "}";
    istringstream in2(f_to_restore);
    auto facility3 = Facility::deserialize(in2);
    if (facility3 != nullptr) {
        facility3->display(true);
    } else {
        cout << "Failed to restore facility from string." << endl;
    }

    delete facility;
    return 0;
}
