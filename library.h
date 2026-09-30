#ifndef LIBRARY_H
#define LIBRARY_H

#include "LectureBuilding.h"

using namespace std;
class Library : public LectureBuilding {
private:
    string locatedIn;

public:
    Library(
        string n,
        int xPos,
        int yPos,
        int floors,
        int classrooms,
        bool labs,
        bool lift,
        string blockName
    );

    void displayDetails() const override;

    string getLocatedIn() const { return locatedIn; }
    void setLocatedIn(string blockName) { locatedIn = blockName; }

    string getType() const override {
        return "Library";
    }
};

#endif