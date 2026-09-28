#ifndef CANTEEN_H
#define CANTEEN_H

#include "CampusLocation.h"

class Canteen : public CampusLocation {
private:
    int seatingCapacity;
    bool servesVeg;
    bool servesNonVeg;
    std::string openingTime;
    std::string closingTime;

public:
    Canteen(std::string n, int xPos, int yPos);

    void displayDetails() const override;

    void setSeatingCapacity(int capacity);
    void setServesVeg(bool veg);
    void setServesNonVeg(bool nonVeg);
    void setOpeningTime(std::string time);
    void setClosingTime(std::string time);
};