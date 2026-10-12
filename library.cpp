#include "library.h"

using namespace std;
Library::Library(string n, int floors, int classrooms, bool labs, bool lift, string blockName)
    : LectureBuilding(n, floors, classrooms, labs ? 1 : 0, lift ? 1 : 0), locatedIn(blockName) {}

void Library::displayDetails() const {
    cout << "\n========================================\n";
    cout << "            LIBRARY DETAILS             \n";
    cout << "========================================\n";
    cout << "Name: " << name << "\n";
    cout << "Floors: " << floorCount << "\n";
    cout << "Classrooms: " << classroomCount << "\n";
    cout << "Labs: " << labCount << "\n";
    cout << "Lifts: " << liftCount << "\n";
    cout << "Located in Block: " << locatedIn << "\n";
} 