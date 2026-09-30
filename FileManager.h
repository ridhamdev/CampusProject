#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "CampusLocation.h"
#include "Canteen.h"
#include "Gate.h"
#include "Hostel.h"
#include "LectureBuilding.h"
#include "library.h"
#include "Parking.h"
#include "sportsFacility.h"

#include "User.h"
#include "Student.h"
#include "Admin.h"

#include "Report.h"

using namespace std;

class FileManager {
private:
    string usersFilename;
    string locationsFilename;
    string reportsFilename;

public:
    FileManager(
        string usersFile = "data/User.txt",
        string locationsFile = "data/locations.txt",
        string reportsFile = "data/reports.txt"
    );

    // Users
    void saveUsers(const vector<User*>& users);
    vector<User*> loadUsers();

    // Locations
    void saveLocations(const vector<CampusLocation*>& locations);
    vector<CampusLocation*> loadLocations();

    // Reports
    void saveReports(const vector<Report>& reports);
    vector<Report> loadReports();
};

#endif