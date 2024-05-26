#include "Portfolio.h"

// Constructor
Portfolio::Portfolio() {}

// Getters
std::vector<Part>& Portfolio::getParts() {
    return parts;
}

// Other methods
void Portfolio::addPart(const Part& part) {
    parts.push_back(part);
}

double Portfolio::calculateTotalInterest() const {
    double totalInterest = 0;
    for (const auto& part : parts) {
        totalInterest += part.getInterest();
    }
    return totalInterest;
}

double Portfolio::getRemainingAmount() const {
    double totalRepaid = 0;
    for (const auto& part : parts) {
        totalRepaid += part.getRepaidAmount();
    }
    return totalRepaid;
}
