#ifndef HOSTEL_H
#define HOSTEL_H

#include "CampusLocation.h"

class Hostel : public CampusLocation {
private:
    int roomCount;
    int capacity;
    bool hasWarden;
    bool hasAccessibleEntrance;

public:
    Hostel(std::string n, int xPos, int yPos);

    void displayDetails() const override;

    void setRoomCount(int rooms);
    void setCapacity(int students);
    void setWarden(bool warden);
    void setAccessibleEntrance(bool accessible);
};

#endif