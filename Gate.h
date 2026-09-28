#ifndef GATE_H
#define GATE_H

#include "CampusLocation.h"

class Gate : public CampusLocation {
private:
    std::string openingTime;
    std::string closingTime;
    bool securityAvailable;
    bool isOpen;

public:
    Gate(std::string n, int xPos, int yPos);

    void displayDetails() const override;

    void setOpeningTime(std::string time);
    void setClosingTime(std::string time);
    void setSecurity(bool security);
    void setOpen(bool open);
};

#endif