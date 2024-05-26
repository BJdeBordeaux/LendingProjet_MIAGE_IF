#include <iostream>
#include <vector>
#include "Deal.h"
#include "Facility.h"
#include "Part.h"
#include "Portfolio.h"
#include "Borrower.h"
#include "Lender.h"
#include "Account.h"

int main() {
    // Create accounts for Borrowers and Lenders
    Account borrowerAccount("USD", 0.0);
    Account lender1Account("USD", 1000000.0);
    Account lender2Account("USD", 1000000.0);

    // Create Borrowers and Lenders
    Borrower borrower("Air France", borrowerAccount);
    Lender lender1("Bank of America", lender1Account);
    Lender lender2("Wells Fargo", lender2Account);

    // Create a Deal
    Deal deal("SZB1234", "JP Morgan", {"Bank of America", "Wells Fargo"}, "Air France", 2000000.0, "USD", "2024-05-01", "2034-05-01", "closed");

    // Create Facilities
    Facility facility1("2024-05-01", "2029-05-01", 1000000.0, "USD", {"Bank of America"});
    Facility facility2("2024-05-01", "2029-05-01", 1000000.0, "USD", {"Wells Fargo"});

    // Add Facilities to Deal
    deal.addFacility(facility1);
    deal.addFacility(facility2);

    // Create Parts (repayments)
    Part part1(200000.0, 5000.0);
    Part part2(300000.0, 7500.0);

    // Add Parts to Facilities
    facility1.addPart(part1);
    facility2.addPart(part2);

    // Add Parts to Portfolio
    borrower.getPortfolio().addPart(part1);
    borrower.getPortfolio().addPart(part2);

    // Simulate transactions
    borrower.getAccount().deposit(500000.0); // Borrower receives loan
    lender1.getAccount().withdraw(500000.0); // Lender 1 lends money
    lender2.getAccount().withdraw(500000.0); // Lender 2 lends money

    // Print out the details
    std::cout << "Deal Details:" << std::endl;
    std::cout << "Contract Number: " << deal.getContractNumber() << std::endl;
    std::cout << "Agent: " << deal.getAgent() << std::endl;
    std::cout << "Borrower: " << deal.getBorrower() << std::endl;
    std::cout << "Project Amount: $" << deal.getProjectAmount() << std::endl;
    std::cout << "Currency: " << deal.getCurrency() << std::endl;
    std::cout << "Start Date: " << deal.getStartDate() << std::endl;
    std::cout << "End Date: " << deal.getEndDate() << std::endl;
    std::cout << "Status: " << deal.getStatus() << std::endl;

    std::cout << "\nFacilities:" << std::endl;
    for (int i = 0; i < deal.getFacilities().size(); ++i) {
        std::cout << "Facility " << i+1 << ": $" << deal.getFacilities()[i].getAmount() << ", Lenders: ";
        for (const auto& lender : deal.getFacilities()[i].getLenders()) {
            std::cout << lender << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "\nBorrower Account Balance: $" << borrower.getAccount().getBalance() << std::endl;
    std::cout << "Lender 1 Account Balance: $" << lender1.getAccount().getBalance() << std::endl;
    std::cout << "Lender 2 Account Balance: $" << lender2.getAccount().getBalance() << std::endl;

    return 0;
}
