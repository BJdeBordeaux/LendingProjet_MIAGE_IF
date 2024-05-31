#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <fstream>
#include "Deal.h"
#include "Facility.h"
#include "Borrower.h"
#include "Lender.h"
#include "Portfolio.h"
#include "utils/Utils.h"

using namespace std;

vector<Borrower*> borrowers;
vector<Account*> accounts;
vector<Lender*> lenders;
vector<Portfolio*> portfolios;
vector<Facility*> facilities;
vector<Deal*> deals;
vector<Part*> parts;

void displayBorrowers() {
    cout << "Display Borrowers:" << endl;
    for (const auto& borrower : borrowers) {
        borrower->display();
    }
}

void displayLenders() {
    cout << "Display Lenders:" << endl;
    for (const auto& lender : lenders) {
        lender->display();
    }
}

void displayDeals() {
    cout << "Display Deals:" << endl;
    for (const auto& deal : deals) {
        deal->display();
    }
}

Deal* createDeal() {
    string contractNumber, agent, borrowerName;
    cout << "Enter contract number: ";
    cin >> contractNumber;
    cout << "Enter agent: ";
    getline(cin >> ws, agent);
    cout << "Enter borrower: ";
    getline(cin >> ws, borrowerName);

    auto borrower = new Borrower(borrowerName);
    borrowers.push_back(borrower);

    char addMore;
    do {
        string startDate, endDate, currency;
        cout << "Enter facility start date (YYYY-MM-DD): ";
        cin >> startDate;
        cout << "Enter facility end date (YYYY-MM-DD): ";
        cin >> endDate;
        cout << "Enter facility currency: ";
        cin >> currency;

        vector<double> lenderAmounts;
        vector<string> facilityLenders;
        char addLender;
        do {
            string lenderName;
            double amount;
            cout << "Enter lender name: ";
            getline(cin >> ws, lenderName);
            cout << "Enter amount: ";
            cin >> amount;

            facilityLenders.push_back(lenderName);
            lenderAmounts.push_back(amount);

            cout << "Add another lender to this facility? (y/n): ";
            cin >> addLender;
        } while (addLender == 'y');

        auto facility = new Facility(startDate, endDate, lenderAmounts, currency, facilityLenders);
        facilities.push_back(facility);

        // add facility to lender's portfolio
        for (const auto& lenderName : facilityLenders) {
            for (const auto& lender : lenders) {
                if (lender->getName() == lenderName) {
                    lender->getPortfolio()->addFacility(facility);
                }
            }
        }

        cout << "Add another facility? (y/n): ";
        cin >> addMore;
    } while (addMore == 'y');

    auto deal = new Deal(contractNumber, agent, borrowerName, facilities);
    deals.push_back(deal);

    cout << "Deal created successfully." << endl;

    return deal;
}

Borrower* createBorrower() {
    string name;
    cout << "Enter borrower name: ";
    getline(cin >> ws, name);
    auto borrower = new Borrower(name);
    borrowers.push_back(borrower);

    cout << "Borrower created successfully." << endl;

    return borrower;
}

Lender* createLender() {
    string name;
    cout << "Enter lender name: ";
    getline(cin >> ws, name);
    auto lender = new Lender(name);
    lenders.push_back(lender);

    cout << "Lender created successfully." << endl;

    return lender;
}

void displayBorrowerDeals() {
    string borrowerName;
    cout << "Enter borrower name: ";
    getline(cin >> ws, borrowerName);
    cout << "Deals for borrower " << borrowerName << ":" << endl;
    for (const auto& deal : deals) {
        if (deal->getBorrower() == borrowerName) {
            deal->display();
        }
    }
}

void repayFacility() {
    string borrowerName;
    cout << "Enter borrower name: ";
    getline(cin >> ws, borrowerName);
    string contractNumber;
    bool dealFound;
    Deal *deal = nullptr;
    do {
        dealFound = false;
        cout << "Enter Deal contract Number: ";
        cin >> contractNumber;
        // find the Deal
        for (const auto &d: deals) {
            if (d->getContractNumber() == contractNumber && d->getBorrower() == borrowerName) {
                dealFound = true;
                deal = d;
                break;
            }
        }
        if (!dealFound) {
            cout << "Deal not found." << endl;
            continue;
        }

        // find the Facility
        int facilityIndex;
        do {
            deal->display(true);
            cout << "Enter Facility to repay (an integer starting from 1): ";
            cin >> facilityIndex;
        } while (facilityIndex < 1 || facilityIndex > deal->getFacilities().size());
        Facility *facility = deal->getFacilities()[facilityIndex - 1];

        // enter amount to repay
        double amountToRepay = -1;
        double remainingInterest = facility->calculateRemainingInterestAmount();
        cout << setprecision(2) << fixed << "Remaining interest amountToRepay: " << remainingInterest << endl;
        do {
            cout << "Enter amountToRepay to repay: ";
            cin >> amountToRepay;
        } while (amountToRepay < -0.01 || (amountToRepay > facility->calculateRemainingInterestAmount()+0.01));

        // create a new part
        auto part = new Part(borrowerName, amountToRepay);
        facility->addPart(part);

        cout << "Facility repaid successfully, remaining interest amount: " << facility->calculateRemainingInterestAmount() << endl;

    } while (!dealFound);

}

void displayLenderDeals() {
    string lenderName;
    cout << "Enter lender name: ";
    getline(cin >> ws, lenderName);
    cout << "Deals for lender " << lenderName << ":" << endl;
    for (const auto& deal : deals) {
        // if Lender is not Deal's agent or not in pool, skip
        if (deal->getAgent() != lenderName) {
            bool found = false;
            for (const auto& lenderInPool: deal->getPool()) {
                if (lenderInPool == lenderName) {
                    found = true;
                    break;
                }
            }
            if (!found) continue;
        }
        deal->display();
    }
}

void displayLenderPortfolio() {
    string lenderName;
    cout << "Enter lender name: ";
    getline(cin >> ws, lenderName);
    cout << "Portfolio for lender " << lenderName << ":" << endl;
    // Assuming we have a way to get a lender's portfolio
    for (const auto& lender : lenders) {
        if (lender->getName() == lenderName) {
            auto portfolio = lender->getPortfolio();
            portfolio->display();
        }
    }
}

void displayMenu() {
    int choice;
    do {
        cout << "Menu:" << endl;
        cout << "1. Display information" << endl;
        cout << "2. Create" << endl;
        cout << "3. Management" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cout << endl;

        switch (choice) {
            case 1: {
                int subChoice_1;
                do {
                    cout << "1. Display Borrowers" << endl;
                    cout << "2. Display Lenders" << endl;
                    cout << "3. Display Deals" << endl;
                    cout << "4. Back" << endl;
                    cout << "Enter your choice: ";
                    cin >> subChoice_1;
                    cout << endl;
                    if (subChoice_1 == 1) displayBorrowers();
                    else if (subChoice_1 == 2) displayLenders();
                    else if (subChoice_1 == 3) displayDeals();
                    else if (subChoice_1 == 4) break;
                    else cout << "Invalid choice. Please try again." << endl;
                } while (subChoice_1 != 4);
                break;
            }
            case 2: {
                int subChoice2;
                do {
                    cout << "1. Create Deal" << endl;
                    cout << "2. Create Borrower" << endl;
                    cout << "3. Create Lender" << endl;
                    cout << "4. Back" << endl;
                    cout << "Enter your choice: ";
                    cin >> subChoice2;
                    cout << endl;
                    if (subChoice2 == 1) createDeal();
                    else if (subChoice2 == 2) createBorrower();
                    else if (subChoice2 == 3) createLender();
                    else if (subChoice2 == 4) break;
                    else cout << "Invalid choice. Please try again." << endl;
                } while (subChoice2 != 4);
                break;
            }
            case 3: {
                int subChoice3;
                do {
                    cout << "1. Borrower Management" << endl;
                    cout << "2. Lender Management" << endl;
                    cout << "3. Back" << endl;
                    cout << "Enter your choice: ";
                    cin >> subChoice3;
                    cout << endl;
                    if (subChoice3 == 1) {
                        do {
                            cout << "1. See borrower's deals" << endl;
                            cout << "2. Repay facility" << endl;
                            cout << "3. Back" << endl;
                            cin >> subChoice3;
                            if (subChoice3 == 1) displayBorrowerDeals();
                            else if (subChoice3 == 2) repayFacility();
                            else if (subChoice3 == 3) break;
                        } while (subChoice3 != 2);
                    } else if (subChoice3 == 2) {
                        do {
                            cout << "1. See lender's deals" << endl;
                            cout << "2. See lender's portfolio" << endl;
                            cout << "3. Back" << endl;
                            cin >> subChoice3;
                            if (subChoice3 == 1) displayLenderDeals();
                            else if (subChoice3 == 2) displayLenderPortfolio();
                            else if (subChoice3 == 3) break;
                        } while (subChoice3 != 3);
                    } else if (subChoice3 == 3) break;
                    else cout << "Invalid choice. Please try again." << endl;
                } while (subChoice3 != 3);
                break;
            }
            case 4: {
                cout << "Exiting..." << endl;
                break;
            }
            default: {
                cout << "Invalid choice. Please try again." << endl;
                break;
            }
        }
    } while (choice != 4);
}

void prepareDemoData(){
    // prepare data
    auto lender1 = new Lender("Credit Agricole");
    auto lender2 = new Lender("Societe Generale");
    auto lender3 = new Lender("BNP Paribas");
    lenders.push_back(lender1);
    lenders.push_back(lender2);
    lenders.push_back(lender3);

    auto borrower = new Borrower("Air France");
    borrowers.push_back(borrower);

    vector<double> lenderAmounts1 = vector<double>{1000, 2000};
    vector<string> lendersVect1 = vector<string>{lender1->getName(), lender2->getName()};
    vector<double> lenderAmounts2 = vector<double>{100, 200};
    vector<string> lendersVect2 = vector<string>{lender1->getName(), lender3->getName()};
    auto facility1 = new Facility("2021-02-01", "2021-12-31", lenderAmounts1, "USD", lendersVect1);
    auto facility2 = new Facility("2021-01-01", "2021-11-30", lenderAmounts2, "EUR", lendersVect2);
    auto facility3 = new Facility("2021-06-01", "2022-11-30", lenderAmounts2, "EUR", lendersVect1);
    auto deal1 = new Deal("S0001", lender1->getName(), borrower->getName(), vector<Facility*>{facility1, facility2, facility3});

    // add Facilities to Lenders' portfolios
    for (auto &createdFacility: {facility1, facility2, facility3}) {
        for (auto &facilityLender: createdFacility->getLenders()) {
            for (auto &lender: lenders) {
                if (lender->getName() == facilityLender) {
                    lender->getPortfolio()->addFacility(createdFacility);
                }
            }
        }
    }

    // add to vectors
    facilities.push_back(facility1);
    facilities.push_back(facility2);
    facilities.push_back(facility3);
    for (auto &lender: lenders) {
        portfolios.push_back(lender->getPortfolio());
    }

    deals.push_back(deal1);


}

void setUp(){
    cout << "Setting up..." << endl;
    // get information from files
    // Borrowers
    ifstream borrowersFile("borrowers.txt");
    if (borrowersFile.is_open()) {
        do {
            Borrower *borrower = Borrower::deserialize(borrowersFile);
            if (borrower) {
                borrowers.push_back(borrower);
            } else {
                break;
            }
        } while (!borrowersFile.eof());
        borrowersFile.close();
    } else {
        cerr << "Unable to open borrowers file." << endl;
    }
    cout << "Borrowers loaded." << endl;

    // Lenders
    ifstream lendersFile("lenders.txt");
    if (lendersFile.is_open()) {
        do {
            Lender *lender = Lender::deserialize(lendersFile);
            if (lender) {
                lenders.push_back(lender);
            } else {
                break;
            }
        } while (!lendersFile.eof());
        lendersFile.close();
    } else {
        cerr << "Unable to open lenders file." << endl;
    }
    cout << "Lenders loaded." << endl;

    // Deals
    ifstream dealsFile("deals.txt");
    if (dealsFile.is_open()) {
        string line;
        // while it is not end of file, read a deal
        do {
            Deal *deal = Deal::deserialize(dealsFile);
            if (deal) {
                deals.push_back(deal);
            } else {
                break;
            }
        } while (!dealsFile.eof());

        dealsFile.close();
    } else {
        cerr << "Unable to open deals file." << endl;
    }
    cout << "Deals loaded." << endl;

    // add each facility to its lenders portfolio
    for (auto *deal: deals) {
        for (auto *facility: deal->getFacilities()) {
            for (const auto& lenderName: facility->getLenders()) {
                for (auto &lender: lenders) {
                    if (lender->getName() == lenderName) {
                        lender->getPortfolio()->addFacility(facility);
                    }
                }
            }
        }
    }
    cout << "Facilities added to lenders' portfolios." << endl;

    // add all to vectors
    for (auto *lender: lenders) {
        portfolios.push_back(lender->getPortfolio());
        // account
        for (auto &account: lender->getPortfolio()->getCurrencyAccounts()) {
            accounts.push_back(account);
        }
    }
    cout << "Portfolio, Account added to vectors." << endl;

    for (auto *deal: deals) {
        for (auto *facility: deal->getFacilities()) {
            facilities.push_back(facility);
            for (auto *part: facility->getParts()) {
                parts.push_back(part);
            }
        }
    }
    cout << "Facilities, Parts added to vectors." << endl;
    cout << "Data set up successfully." << endl;
}

void saveData(){
    // save data to files
    // Borrowers
    ofstream borrowersFile("borrowers.txt");
    if (borrowersFile.is_open()) {
        for (const auto& borrower : borrowers) {
            borrower->serialize(borrowersFile);
        }
        borrowersFile.close();
    } else {
        cerr << "Unable to open borrowers file." << endl;
    }

    // Lenders
    ofstream lendersFile("lenders.txt");
    if (lendersFile.is_open()) {
        for (const auto& lender : lenders) {
            lender->serialize(lendersFile);
        }
        lendersFile.close();
    } else {
        cerr << "Unable to open lenders file." << endl;
    }

    // Deals
    ofstream dealsFile("deals.txt");
    if (dealsFile.is_open()) {
        for (const auto& deal : deals) {
            deal->serialize(dealsFile);
        }
        dealsFile.close();
    } else {
        cerr << "Unable to open deals file." << endl;
    }

}

int main() {
    prepareDemoData();
//    setUp();
    displayMenu();
//    saveData();
    return EXIT_SUCCESS;
}


