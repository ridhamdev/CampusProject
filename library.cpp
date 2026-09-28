#include "library.h"

using namespace std;
Library::Library(string n, int xPos, int yPos, int floors, int classrooms, bool labs, bool lift, string blockName)
    : LectureBuilding(n, xPos, yPos, floors, classrooms, labs ? 1 : 0, lift ? 1 : 0), locatedIn(blockName) {}

void Library::displayDetails() const {
    cout << "\n========================================\n";
    cout << "            LIBRARY DETAILS             \n";
    cout << "========================================\n";
    cout << "Name: " << name << "\n";
    cout << "Location: (" << x << ", " << y << ")\n";
    cout << "Floors: " << floorCount << "\n";
    cout << "Classrooms: " << classroomCount << "\n";
    cout << "Labs: " << labCount << "\n";
    cout << "Lifts: " << liftCount << "\n";
    cout << "Located in Block: " << locatedIn << "\n";
} 