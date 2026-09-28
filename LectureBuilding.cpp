#include<iostream>
#include<string>
#include "LectureBuilding.h"
using namespace std;
LectureBuilding::LectureBuilding(string n,int xpos,int ypos,int floors,int classrooms,int labs,int lifts)
    : CampusLocation(n,xpos,ypos),floorCount(floors),classroomCount(classrooms),labCount(labs),liftCount(lifts) {}

void LectureBuilding::displayDetails() const {
    cout << "\n========================================\n";
    cout << "        LECTURE BUILDING DETAILS        \n";
    cout << "========================================\n";
    cout << "Name: " << name << "\n";
    cout << "Location: (" << x << ", " << y << ")\n";
    cout << "Floors: " << floorCount << "\n";
    cout << "Classrooms: " << classroomCount << "\n";
    cout << "Labs: " << labCount << "\n";
    cout << "Lifts: " << liftCount << "\n";
}

void LectureBuilding::setFloorCount(int floors) {
    floorCount = floors;
}
void LectureBuilding::setClassroomCount(int classrooms) {
    classroomCount = classrooms;
}
void LectureBuilding::setLabCount(int labs){
    labCount = labs;
}
void LectureBuilding::setLiftCount(int lifts){
    liftCount = lifts;
}

