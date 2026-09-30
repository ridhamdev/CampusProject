#ifndef SPORTS_FACILITY_H
#define SPORTS_FACILITY_H

#include "CampusLocation.h"
using namespace std;
class SportsFacility : public CampusLocation {
private:
    std::string sport;
    bool isAvailable;

public:
    SportsFacility(string n, int xPos, int yPos);

    void displayDetails() const override;

    void setSport(string sportName);
    void setAvailable(bool available);

    string getSport() const { return sport; }
    bool getIsAvailable() const { return isAvailable; }

    string getType() const override {
        return "SportsFacility";
    }
};

#endif
