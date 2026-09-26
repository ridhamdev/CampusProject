#ifndef CAMPUS_LOCATION_H
#define CAMPUS_LOCATION_H

#include <string>
#include <iostream>
using namespace std;

class CampusLocation {
protected:
    string name;
    int x;
    int y;
    bool rampAvailable;
    bool elevatorAvailable;
    bool accessibleEntrance;
    bool accessibleRestroom;

public:
    CampusLocation(string n, int xPos, int yPos);
    virtual ~CampusLocation() {}

    string getName() const;
    int getX() const;
    int getY() const;

    void setAccessibility(bool ramp, bool elevator, bool entrance, bool restroom);
    void displayAccessibility() const;

    virtual void displayDetails() const = 0;
    virtual string getType() const = 0;
};

#endif