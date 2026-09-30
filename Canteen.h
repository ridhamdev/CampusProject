#ifndef CANTEEN_H
#define CANTEEN_H
#include <iostream>
#include "CampusLocation.h"
using namespace std;
class Canteen : public CampusLocation {
private:
    int seatingCapacity;
    string openingTime;
    string closingTime;

public:
    Canteen(string canteenName, int seatingCapacity, string openingTime, string closingTime, int xPos, int yPos);

    void displayDetails() const override;

    void setSeatingCapacity(int capacity);
    void setOpeningTime(string time);
    void setClosingTime(string time);

    int getSeatingCapacity() const { return seatingCapacity; }
    string getOpeningTime() const { return openingTime; }
    string getClosingTime() const { return closingTime; }

    string getType() const override {
        return "Canteen";
    }
};

#endif