#ifndef HOSTEL_H
#define HOSTEL_H

#include "CampusLocation.h"
using namespace std;
class Hostel : public CampusLocation {
private:
    int roomCount;
    int capacity;
    bool hasWarden;
    bool hasAccessibleEntrance;

public:
    Hostel(string n, int xPos, int yPos);

    void displayDetails() const override;

    void setRoomCount(int rooms);
    void setCapacity(int students);
    void setWarden(bool warden);
    void setAccessibleEntrance(bool accessible);

    int getRoomCount() const { return roomCount; }
    int getCapacity() const { return capacity; }
    bool getHasWarden() const { return hasWarden; }
    bool getHasAccessibleEntrance() const { return hasAccessibleEntrance; }

    string getType() const override {
        return "Hostel";
    }
};

#endif