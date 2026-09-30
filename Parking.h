#ifndef PARKING_H
#define PARKING_H

#include "CampusLocation.h"
using namespace std;

class Parking : public CampusLocation {
private:
    int totalSpots;
    string parkingType;
public:
    Parking(string name, string parkingType, int xPos, int yPos);

    void displayDetails() const override;

    void setTotalSpots(int spots);
    void setParkingType(string type);

    int getTotalSpots() const { return totalSpots; }
    string getParkingType() const { return parkingType; }

    string getType() const override {
        return "Parking";
    }
};

#endif