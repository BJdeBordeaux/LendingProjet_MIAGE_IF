#include "Part.h"

// Constructor
Part::Part(double repaidAmount, double interest)
        : repaidAmount(repaidAmount), interest(interest) {}

// Getters
double Part::getRepaidAmount() const {
    return repaidAmount;
}

double Part::getInterest() const {
    return interest;
}

// Other methods
double Part::calculateInterest(double rate, int period) {
    // Example simple interest calculation
    interest = repaidAmount * rate * period / 100.0;
    return interest;
}

void Part::updateAmount(double amount) {
    repaidAmount += amount;
    // Optionally, recalculate interest if required
    // interest = calculateInterest(some_rate, some_period);
}
