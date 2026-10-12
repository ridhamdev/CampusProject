#include "sportsFacility.h"

using namespace std;

SportsFacility::SportsFacility(string n)
: CampusLocation(n), sport(""), isAvailable(false) {}

void SportsFacility::displayDetails() const {
    cout << "\n========================================\n";
    cout << "         SPORTS FACILITY DETAILS        \n";
    cout << "========================================\n";
    cout << "Name: " << name << "\n";
    cout << "Sport: " << sport << "\n";
    cout << "Availability: " << (isAvailable ? "Available" : "Not Available") << "\n";
}

void SportsFacility::setSport(string sportName) {
    sport = sportName;
}

void SportsFacility::setAvailable(bool available) {
    isAvailable = available;
}