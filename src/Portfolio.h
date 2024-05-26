#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include <vector>
#include "Part.h"

class Portfolio {
public:
    // Constructor
    Portfolio();

    // Getters
    std::vector<Part>& getParts();

    // Other methods
    void addPart(const Part& part);
    double calculateTotalInterest() const;
    double getRemainingAmount() const;

private:
    std::vector<Part> parts;
};

#endif // PORTFOLIO_H
