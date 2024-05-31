#include "Borrower.h"
#include <iostream>
#include <fstream>

using namespace std;

int main() {
    // test all method
    Borrower borrower("Borrower");
    cout << borrower.getName() << endl;
    borrower.display();

    // Create a borrower object
    Borrower* borrower1 = new Borrower("John Doe");

    // Serialize the borrower object to a file
    ofstream outFile("borrowerSerialization.txt");
    if (outFile.is_open()) {
        borrower1->serialize(outFile);
        outFile.close();
        cout << "Borrower saved to file." << endl;
    } else {
        cerr << "Unable to open file for writing." << endl;
    }

    // Deserialize the borrower object from the file
    ifstream inFile("borrowerSerialization.txt");
    if (inFile.is_open()) {
        Borrower* restoredBorrower = Borrower::deserialize(inFile);
        inFile.close();
        if (restoredBorrower != nullptr) {
            cout << "Borrower restored from file:" << endl;
            restoredBorrower->display();
            delete restoredBorrower; // Don't forget to free the memory
        } else {
            cerr << "Failed to restore borrower from file." << endl;
        }
    } else {
        cerr << "Unable to open file for reading." << endl;
    }

    delete borrower1; // Free the memory
}