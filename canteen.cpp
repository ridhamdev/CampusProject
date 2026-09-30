#include "Canteen.h"

using namespace std;


Canteen::Canteen(string canteenName, int seatingCapacity, string openingTime, string closingTime, int xPos, int yPos)
: CampusLocation(canteenName,xPos, yPos), seatingCapacity(seatingCapacity), openingTime(openingTime), closingTime(closingTime) {}

void Canteen::displayDetails() const {
    cout << "\n========================================\n";
    cout << "            CANTEEN DETAILS             \n";
    cout << "========================================\n";
    cout << "Name: " << name << "\n";
    cout << "Location: (" << x << ", " << y << ")\n";
    cout << "Seating Capacity: " << seatingCapacity << "\n";
    cout << "Opening Time: " << openingTime << "\n";
    cout << "Closing Time: " << closingTime << "\n";
}

void Canteen::setSeatingCapacity(int capacity) {
    seatingCapacity = capacity;
}

void Canteen::setOpeningTime(string time) {
    openingTime = time;
}

void Canteen::setClosingTime(string time) {
    closingTime = time;
}