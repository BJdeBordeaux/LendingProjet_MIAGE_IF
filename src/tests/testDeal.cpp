#include "Deal.h"
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int main(){

    // prepare data
    vector<double> lenderAmounts1 = vector<double>{1000, 2000};
    vector<string> lenders1 = vector<string>{"lenderA1", "lenderA2"};
    vector<double> lenderAmounts2 = vector<double>{100, 200};
    vector<string> lenders2 = vector<string>{"lenderA1", "lenderB2"};
    auto facility1 = new Facility("2021-02-01", "2021-12-31", lenderAmounts1, "USD", lenders1);
    auto facility2 = new Facility("2021-01-01", "2021-11-30", lenderAmounts2, "EUR", lenders2);

    // test all methods
    auto deal = new Deal("S0001", "LenderA1", vector<string>{"Borrower1"}, vector<Facility*>{facility1, facility2});
    deal->display(true);

    // test serialization
    cout << "Serialization and deserialization" << endl;
    ofstream out("dealSerialization.txt");
    if (out.is_open()) {
        deal->serialize(out);
        out.close();
    } else {
        cout << "Unable to open file" << endl;
    }

    ifstream in("dealSerialization.txt");
    if (in.is_open()) {
        auto deal2 = Deal::deserialize(in);
        deal2->display(true);
        in.close();
    } else {
        cout << "Unable to open file" << endl;
    }

    delete deal;

    return EXIT_SUCCESS;
}

