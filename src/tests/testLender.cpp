#include "Lender.h"
#include <iostream>
#include <fstream>

using namespace std;

int main() {
    auto myLender = new Lender("Lender1");
    cout << myLender->getName() << endl;
    cout << myLender->getPortfolio()->getLender() << endl;
    myLender->display();

    // add a facility to Portfolio
    Facility* fac1 = new Facility("2023-01-01", "2024-01-01", vector<double>{10000}, "USD", vector<string>{"Term Loan"});
    // add Part to Facility
    Part* part1 = new Part("Term Loan", 1000);
    fac1->addPart(part1);
    myLender->getPortfolio()->addFacility(fac1);

    // serialization
    ofstream outFile("lenderSerialization.txt");
    if (outFile.is_open()) {
        myLender->serialize(outFile);
        outFile.close();
        cout << "Lender saved to file." << endl;
    } else {
        cerr << "Unable to open file for writing." << endl;
    }

    // deserialization
    ifstream inFile("lenderSerialization.txt");
    if (inFile.is_open()) {
        Lender* restoredLender = Lender::deserialize(inFile);
        inFile.close();
        if (restoredLender != nullptr) {
            cout << "Lender restored from file:" << endl;
            restoredLender->display();
            vector<Facility*> facs = restoredLender->getPortfolio()->getFacilities();
            for (auto f : facs) {
                f->display();
                f->getParts()[0]->display();
            }
            delete restoredLender;
        } else {
            cerr << "Failed to restore lender from file." << endl;
        }
    } else {
        cerr << "Unable to open file for reading." << endl;
    }

    delete myLender;
}
