#include <fstream>
#include "Part.h"

using namespace std;

int main() {
    auto part = new Part("Borrower", 100);
    cout << part->getRepaidAmount() << endl;
    cout << part->getBorrower() << endl;

    // Serialize the part object to a file
    ofstream outFile("partSerialization.txt");
    if (outFile.is_open()) {
        part->serialize(outFile);
        outFile.close();
        cout << "Part saved to file." << endl;
    } else {
        cerr << "Unable to open file for writing." << endl;
    }

    // Deserialize the part object from the file
    ifstream inFile("partSerialization.txt");
    if (inFile.is_open()) {
        Part* restoredPart = Part::deserialize(inFile);
        inFile.close();
        if (restoredPart != nullptr) {
            cout << "Part restored from file:" << endl;
            restoredPart->display();
            delete restoredPart; // Don't forget to free the memory
        } else {
            cerr << "Failed to restore part from file." << endl;
        }
    } else {
        cerr << "Unable to open file for reading." << endl;
    }

    delete part; // Free the memory

    return 0;
}