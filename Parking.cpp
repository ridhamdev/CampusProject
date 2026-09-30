#include "Parking.h"
using namespace std;

Parking::Parking(string n, string type, int xPos, int yPos)
    : CampusLocation(n, xPos, yPos), totalSpots(0), parkingType(type) {}

void Parking::displayDetails() const {
    cout << "\n========================================\n";
    cout << "            PARKING DETAILS             \n";
    cout << "========================================\n";
    cout << "Name: " << name << "\n";
    cout << "Location: (" << x << ", " << y << ")\n";
    cout << "Total Spots: " << totalSpots << "\n";
    cout << "Parking Type: " << parkingType << "\n";
}

void Parking::setTotalSpots(int spots) {
    this->totalSpots = spots;
}

void Parking::setParkingType(string type) {
    this->parkingType = type;
}