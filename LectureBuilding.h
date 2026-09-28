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
};
#endif