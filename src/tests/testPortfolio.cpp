#include "Portfolio.h"
#include "Facility.h"
#include <iostream>
#include <fstream>
#include <sstream>

int main(){

    // test all methods
    vector<double> lenderAmounts1 = vector<double>{1000, 2000};
    vector<string> lenders1 = vector<string>{"lenderA1", "lenderA2"};
    vector<double> lenderAmounts2 = vector<double>{100, 200};
    vector<string> lenders2 = vector<string>{"lenderA1", "lenderB2"};
    auto facility = new Facility("2021-01-01", "2021-12-31", lenderAmounts1, "USD", lenders1);
    auto facility2 = new Facility("2021-01-01", "2021-12-31", lenderAmounts2, "EUR", lenders2);
    auto portfolio2 = new Portfolio("lenderA1", vector<Facility*>{facility, facility2});
    cout << "Portfolio 2 lender: " << portfolio2->getLender() << endl;
    cout << "Portfolio 2 facilities: ";
    for (Facility* aFacility : portfolio2->getFacilities()) {
        cout << "(" << aFacility->getCurrency() << ") ";
    }
    cout << endl;
    cout << "Portfolio 2 all currencies interests: ";
    for (double interest : portfolio2->getAllCurrencyInterests()) {
        cout << interest << ", ";
    }
    cout << endl;

    // test getAccountByCurrency
    cout << "Portfolio 2 account by currencies: " << portfolio2->getAccountByCurrency("USD")->getCurrency() << endl;
    cout << "Portfolio 2 account by currencies: " << portfolio2->getAccountByCurrency("RMB")->getCurrency() << endl;

    // test addFacility
    auto portfolio1 = new Portfolio("lenderA1");
    cout << "Before: " << portfolio1->getAccountByCurrency("USD")->getBalance() << endl;
    portfolio1->addFacility(facility);
    cout << "After: " << portfolio1->getAccountByCurrency("USD")->getBalance() << endl;

    // test recalculateCurrencyInterest
    cout << "Before: " << portfolio1->getAccountByCurrency("EUR")->getBalance() << endl;
    portfolio1->addFacility(facility2);
    cout << "After: " << portfolio1->getAccountByCurrency("EUR")->getBalance() << endl;
    double recalculatedInterest = portfolio1->recalculateCurrencyInterest("EUR");
    cout << "Recalculated interest: " << recalculatedInterest << endl;
    portfolio1->display();
    portfolio2->display();

    // test serialization
    cout << "Serialization and deserialization" << endl;
    ofstream out("portfolioSerialization.txt");
    if (out.is_open()) {
        portfolio1->serialize(out);
        out.close();
    } else {
        cout << "Unable to open file" << endl;
    }

    ifstream in("portfolioSerialization.txt");
    if (in.is_open()) {
        auto portfolio3 = Portfolio::deserialize(in);
        portfolio3->display();
        in.close();
    } else {
        cout << "Unable to open file" << endl;
    }

//    string pf_to_restore_str = "Portfolio: {\n"
//                               "    lender: \n"
//                               "        Lender1\n"
//                               "    facilities: [\n"
//                               "Facility: {\n"
//                               "    startDate: \n"
//                               "        2023-01-01\n"
//                               "    endDate: \n"
//                               "        2024-01-01\n"
//                               "    currency: \n"
//                               "        USD\n"
//                               "    lenderAmounts: [\n"
//                               "        10000\n"
//                               "    ]\n"
//                               "    lenders: [\n"
//                               "        Term Loan\n"
//                               "    ]\n"
//                               "    parts: [\n"
//                               "Part: {\n"
//                               "    borrowers: \n"
//                               "        Term Loan\n"
//                               "    repaidAmount: 1000\n"
//                               "}\n"
//                               "    ]\n"
//                               "}\n"
//                               "    ]\n"
//                               "    currencyAccounts: [\n"
//                               "Account: {\n"
//                               "    currency: \n"
//                               "        USD\n"
//                               "    amount: -1\n"
//                               "}\n"
//                               "    ]\n"
//                               "}";
//
//    istringstream in2(pf_to_restore_str);
//    auto portfolio4 = Portfolio::deserialize(in2);
//    if (portfolio4 != nullptr) {
//        portfolio4->display();
//    } else {
//        cout << "Failed to restore portfolio from string." << endl;
//    }


    return EXIT_SUCCESS;
}