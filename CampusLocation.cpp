#include "CampusLocation.h"
using namespace std;
CampusLocation::CampusLocation(string n, int xPos, int yPos)
    : name(n), x(xPos), y(yPos), rampAvailable(false), elevatorAvailable(false),
      accessibleEntrance(false), accessibleRestroom(false) {}

string CampusLocation::getName() const{
    return name;
} 

int CampusLocation::getX() const{
    return x;
}

int CampusLocation::getY() const{
    return y;
}

void CampusLocation::setName(string newName) {
    name = newName;
}

void CampusLocation::setCoordinates(int newX, int newY) {
    x = newX;
    y = newY;
}

bool CampusLocation::hasRamp() const {
    return rampAvailable;
}

bool CampusLocation::hasElevator() const {
    return elevatorAvailable;
}

bool CampusLocation::hasAccessibleEntrance() const {
    return accessibleEntrance;
}

bool CampusLocation::hasAccessibleRestroom() const {
    return accessibleRestroom;
}

void CampusLocation::setAccessibility(bool ramp, bool elevator, bool entrance, bool restroom) {
    rampAvailable = ramp;
    elevatorAvailable = elevator;
    accessibleEntrance = entrance;
    accessibleRestroom = restroom;
}

 void CampusLocation::displayAccessibility() const {
    cout << "\n========================================\n";
    cout << "        ACCESSIBILITY INFORMATION       \n";
    cout << "========================================\n";
    cout << "Location: " << name << "\n";
    cout << "Ramp:                " << (rampAvailable ? "Available" : "Not Available") << "\n";
    cout << "Elevator:            " << (elevatorAvailable ? "Available" : "Not Available") << "\n";
    cout << "Accessible Entrance: " << (accessibleEntrance ? "Available" : "Not Available") << "\n";
    cout << "Accessible Restroom: " << (accessibleRestroom ? "Available" : "Not Available") << "\n";
}
