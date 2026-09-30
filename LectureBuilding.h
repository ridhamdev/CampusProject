#ifndef LECTURE_BUILDING_H
#define LECTURE_BUILDING_H

#include "CampusLocation.h"
using namespace std;
class LectureBuilding : public CampusLocation {
protected:
    int floorCount;
    int classroomCount;
    int labCount;
    int liftCount;

public:
    LectureBuilding(
        string n,
        int xPos,
        int yPos,
        int floors,
        int classrooms,
        int labs,
        int lifts
    );

    void displayDetails() const override;

    void setFloorCount(int floors);
    void setClassroomCount(int classrooms);
    void setLabCount(int labs);
    void setLiftCount(int lifts);

    int getFloorCount() const { return floorCount; }
    int getClassroomCount() const { return classroomCount; }
    int getLabCount() const { return labCount; }
    int getLiftCount() const { return liftCount; }

    string getType() const override {
        return "LectureBuilding";
    }
};
#endif