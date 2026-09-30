#ifndef GATE_H
#define GATE_H

#include "CampusLocation.h"
using namespace std;
class Gate : public CampusLocation {
private:
    string openingTime;
    string closingTime;
    bool securityAvailable;
    bool isOpen;

public:
    Gate(string n, int xPos, int yPos);

    void displayDetails() const override;

    void setOpeningTime(string time);
    void setClosingTime(string time);
    void setSecurity(bool security);
    void setOpen(bool open);

    string getOpeningTime() const { return openingTime; }
    string getClosingTime() const { return closingTime; }
    bool isSecurityAvailable() const { return securityAvailable; }
    bool getIsOpen() const { return isOpen; }

    string getType() const override {
        return "Gate";
    }
};

#endif