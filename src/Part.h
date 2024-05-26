#ifndef PART_H
#define PART_H

class Part {
public:
    // Constructor
    Part(double repaidAmount, double interest);

    // Getters
    double getRepaidAmount() const;
    double getInterest() const;

    // Other methods
    double calculateInterest(double rate, int period);
    void updateAmount(double amount);

private:
    double repaidAmount;
    double interest;
};

#endif // PART_H
