#include "hostel.h"

using namespace std;

Hostel::Hostel(string n, int xPos, int yPos)
    : CampusLocation(n, xPos, yPos), roomCount(0), capacity(0), hasWarden(false), hasAccessibleEntrance(false) {}

void Hostel::displayDetails() const {
    cout << "\n========================================\n";
    cout << "             HOSTEL DETAILS             \n";
    cout << "========================================\n";
    cout << "Name: " << name << "\n";
    cout << "Location: (" << x << ", " << y << ")\n";
    cout << "Room Count: " << roomCount << "\n";
    cout << "Capacity: " << capacity << "\n";
    cout << "Has Warden: " << (hasWarden ? "Yes" : "No") << "\n";
    cout << "Has Accessible Entrance: " << (hasAccessibleEntrance ? "Yes" : "No") << "\n";
}
void Hostel::setRoomCount(int rooms) {
    roomCount = rooms;
}
void Hostel::setCapacity(int students) {
    capacity = students;
}
void Hostel::setWarden(bool warden) {
    hasWarden = warden;
}
void Hostel::setAccessibleEntrance(bool accessible) {
    hasAccessibleEntrance = accessible;
}
