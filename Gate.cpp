#include "Gate.h"

using namespace std;
Gate::Gate(string n, int xPos, int yPos)
    : CampusLocation(n, xPos, yPos), openingTime("06:30 AM"), closingTime("11:00 PM"), securityAvailable(true), isOpen(true) {}

void Gate::displayDetails() const {
    cout << "\n========================================\n";
    cout << "              GATE DETAILS              \n";
    cout << "========================================\n";
    cout << "Name: " << name << "\n";
    cout << "Location: (" << x << ", " << y << ")\n";
    cout << "Opening Time: " << openingTime << "\n";
    cout << "Closing Time: " << closingTime << "\n";
    cout << "Security Available: " << (securityAvailable ? "Yes" : "No") << "\n";
    cout << "Currently Open: " << (isOpen ? "Yes" : "No") << "\n";
}

void Gate::setOpeningTime(string time) {
    openingTime = time;
}

void Gate::setClosingTime(string time) {
    closingTime = time;
}

void Gate::setSecurity(bool security) {
    securityAvailable = security;
}

void Gate::setOpen(bool open) {
    isOpen = open;
}