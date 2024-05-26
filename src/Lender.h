#ifndef LENDER_H
#define LENDER_H

#include <string>
#include <vector>
#include "Facility.h"
#include "Account.h"

class Lender {
public:
    // Constructor
    Lender(const std::string& name, const Account& account);

    // Getters
    std::string getName() const;
    Account& getAccount();
    std::vector<Facility>& getFacilities();

    // Other methods
    void participateInFacility(const Facility& facility);

private:
    std::string name;
    Account account;
    std::vector<Facility> facilities;
};

#endif // LENDER_H
