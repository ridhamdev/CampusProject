#include "FileManager.h"

using namespace std;

FileManager::FileManager(string usersFile, string locationsFile, string reportsFile)
    : usersFilename(usersFile), locationsFilename(locationsFile), reportsFilename(reportsFile) {}


// ==========================================
//               USERS FILE
// ==========================================

void FileManager::saveUsers(const vector<User*>& users) {
    ofstream outFile(usersFilename);
    if (!outFile) {
        cout << "Error: Could not open " << usersFilename << " for writing.\n";
        return;
    }

    for (const auto* user : users) {
        if (!user) continue;

        const Student* student = dynamic_cast<const Student*>(user);
        if (student) {
            // Format: STUDENT|Name|ID|Course|Year
            outFile << "STUDENT|"
                    << student->getName() << "|"
                    << student->getStudentID() << "|"
                    << student->getCourse() << "|"
                    << student->getYearOfStudy() << "\n";
            continue;
        }

        const Admin* admin = dynamic_cast<const Admin*>(user);
        if (admin) {
            // Format: ADMIN|Name|Password
            outFile << "ADMIN|"
                    << admin->getName() << "|"
                    << admin->getPassword() << "\n";
            continue;
        }
    }

    outFile.close();
}

vector<User*> FileManager::loadUsers() {
    vector<User*> users;
    ifstream inFile(usersFilename);
    if (!inFile) {
        return users;
    }

    string line;
    while (getline(inFile, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string type;
        getline(ss, type, '|');

        if (type == "STUDENT") {
            string name, id, course, yearStr;
            getline(ss, name, '|');
            getline(ss, id, '|');
            getline(ss, course, '|');
            getline(ss, yearStr, '|');

            int year = 1;
            if (!yearStr.empty()) {
                try {
                    year = stoi(yearStr);
                } catch (...) {
                    year = 1;
                }
            }

            users.push_back(new Student(name, "Student", id, course, year));
        } else if (type == "ADMIN") {
            string name, password;
            getline(ss, name, '|');
            getline(ss, password, '|');
            if (password.empty()) password = "admin";

            users.push_back(new Admin(name, "Admin", password));
        }
    }

    inFile.close();
    return users;
}

// ==========================================
//             LOCATIONS FILE
// ==========================================

void FileManager::saveLocations(const vector<CampusLocation*>& locations) {
    ofstream outFile(locationsFilename);
    if (!outFile) {
        cout << "Error: Could not open " << locationsFilename << " for writing.\n";
        return;
    }

    for (const auto* loc : locations) {
        if (!loc) continue;

        // Base fields: Type|Name|X|Y|Ramp|Elevator|Entrance|Restroom
        outFile << loc->getType() << "|"
                << loc->getName() << "|"
                << loc->getX() << "|"
                << loc->getY() << "|"
                << (loc->hasRamp() ? "1" : "0") << "|"
                << (loc->hasElevator() ? "1" : "0") << "|"
                << (loc->hasAccessibleEntrance() ? "1" : "0") << "|"
                << (loc->hasAccessibleRestroom() ? "1" : "0");

        // Specific fields based on type
        const Library* lib = dynamic_cast<const Library*>(loc);
        if (lib) {
            outFile << "|" << lib->getFloorCount()
                    << "|" << lib->getClassroomCount()
                    << "|" << lib->getLabCount()
                    << "|" << lib->getLiftCount()
                    << "|" << lib->getLocatedIn();
            outFile << "\n";
            continue;
        }

        const LectureBuilding* lb = dynamic_cast<const LectureBuilding*>(loc);
        if (lb) {
            outFile << "|" << lb->getFloorCount()
                    << "|" << lb->getClassroomCount()
                    << "|" << lb->getLabCount()
                    << "|" << lb->getLiftCount();
            outFile << "\n";
            continue;
        }

        const Canteen* c = dynamic_cast<const Canteen*>(loc);
        if (c) {
            outFile << "|" << c->getSeatingCapacity()
                    << "|" << c->getOpeningTime()
                    << "|" << c->getClosingTime();
            outFile << "\n";
            continue;
        }

        const Gate* g = dynamic_cast<const Gate*>(loc);
        if (g) {
            outFile << "|" << g->getOpeningTime()
                    << "|" << g->getClosingTime()
                    << "|" << (g->isSecurityAvailable() ? "1" : "0")
                    << "|" << (g->getIsOpen() ? "1" : "0");
            outFile << "\n";
            continue;
        }

        const Hostel* h = dynamic_cast<const Hostel*>(loc);
        if (h) {
            outFile << "|" << h->getRoomCount()
                    << "|" << h->getCapacity()
                    << "|" << (h->getHasWarden() ? "1" : "0")
                    << "|" << (h->getHasAccessibleEntrance() ? "1" : "0");
            outFile << "\n";
            continue;
        }

        const Parking* p = dynamic_cast<const Parking*>(loc);
        if (p) {
            outFile << "|" << p->getTotalSpots()
                    << "|" << p->getParkingType();
            outFile << "\n";
            continue;
        }

        const SportsFacility* s = dynamic_cast<const SportsFacility*>(loc);
        if (s) {
            outFile << "|" << s->getSport()
                    << "|" << (s->getIsAvailable() ? "1" : "0");
            outFile << "\n";
            continue;
        }

        outFile << "\n";
    }

    outFile.close();
}

vector<CampusLocation*> FileManager::loadLocations() {
    vector<CampusLocation*> locations;
    ifstream file(locationsFilename);
    if (!file) {
        return locations;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string type, name, xStr, yStr;
        string rampStr, elevStr, entStr, restStr;

        getline(ss, type, '|');
        getline(ss, name, '|');
        getline(ss, xStr, '|');
        getline(ss, yStr, '|');

        int x = 0, y = 0;
        try {
            if (!xStr.empty()) x = stoi(xStr);
            if (!yStr.empty()) y = stoi(yStr);
        } catch (...) {
            x = 0; y = 0;
        }

        bool ramp = false, elevator = false, entrance = false, restroom = false;
        if (getline(ss, rampStr, '|')) ramp = (rampStr == "1" || rampStr == "true");
        if (getline(ss, elevStr, '|')) elevator = (elevStr == "1" || elevStr == "true");
        if (getline(ss, entStr, '|')) entrance = (entStr == "1" || entStr == "true");
        if (getline(ss, restStr, '|')) restroom = (restStr == "1" || restStr == "true");

        CampusLocation* newLoc = nullptr;

        if (type == "Canteen") {
            string capStr, openTime, closeTime;
            getline(ss, capStr, '|');
            getline(ss, openTime, '|');
            getline(ss, closeTime, '|');

            int cap = 100;
            try { if (!capStr.empty()) cap = stoi(capStr); } catch (...) {}
            if (openTime.empty()) openTime = "08:00 AM";
            if (closeTime.empty()) closeTime = "08:00 PM";

            newLoc = new Canteen(name, cap, openTime, closeTime, x, y);
        } else if (type == "Gate") {
            string openTime, closeTime, secStr, openStr;
            getline(ss, openTime, '|');
            getline(ss, closeTime, '|');
            getline(ss, secStr, '|');
            getline(ss, openStr, '|');

            Gate* g = new Gate(name, x, y);
            if (!openTime.empty()) g->setOpeningTime(openTime);
            if (!closeTime.empty()) g->setClosingTime(closeTime);
            if (!secStr.empty()) g->setSecurity(secStr == "1");
            if (!openStr.empty()) g->setOpen(openStr == "1");
            newLoc = g;
        } else if (type == "Hostel") {
            string roomsStr, capStr, wardenStr, accEntStr;
            getline(ss, roomsStr, '|');
            getline(ss, capStr, '|');
            getline(ss, wardenStr, '|');
            getline(ss, accEntStr, '|');

            Hostel* h = new Hostel(name, x, y);
            try {
                if (!roomsStr.empty()) h->setRoomCount(stoi(roomsStr));
                if (!capStr.empty()) h->setCapacity(stoi(capStr));
            } catch (...) {}
            if (!wardenStr.empty()) h->setWarden(wardenStr == "1");
            if (!accEntStr.empty()) h->setAccessibleEntrance(accEntStr == "1");
            newLoc = h;
        } else if (type == "Library") {
            string floorsStr, classStr, labsStr, liftStr, blockStr;
            getline(ss, floorsStr, '|');
            getline(ss, classStr, '|');
            getline(ss, labsStr, '|');
            getline(ss, liftStr, '|');
            getline(ss, blockStr, '|');

            int floors = 2, classrooms = 5;
            bool labs = true, lift = true;
            try {
                if (!floorsStr.empty()) floors = stoi(floorsStr);
                if (!classStr.empty()) classrooms = stoi(classStr);
            } catch (...) {}
            if (!labsStr.empty()) labs = (labsStr == "1" || labsStr == "true");
            if (!liftStr.empty()) lift = (liftStr == "1" || liftStr == "true");
            if (blockStr.empty()) blockStr = "Main Block";

            newLoc = new Library(name, x, y, floors, classrooms, labs, lift, blockStr);
        } else if (type == "LectureBuilding" || type == "Lecture Building") {
            string floorsStr, classStr, labsStr, liftStr;
            getline(ss, floorsStr, '|');
            getline(ss, classStr, '|');
            getline(ss, labsStr, '|');
            getline(ss, liftStr, '|');

            int floors = 3, classrooms = 10, labs = 2, lifts = 1;
            try {
                if (!floorsStr.empty()) floors = stoi(floorsStr);
                if (!classStr.empty()) classrooms = stoi(classStr);
                if (!labsStr.empty()) labs = stoi(labsStr);
                if (!liftStr.empty()) lifts = stoi(liftStr);
            } catch (...) {}

            newLoc = new LectureBuilding(name, x, y, floors, classrooms, labs, lifts);
        } else if (type == "Parking") {
            string spotsStr, pType;
            getline(ss, spotsStr, '|');
            getline(ss, pType, '|');

            if (pType.empty()) pType = "General";
            Parking* p = new Parking(name, pType, x, y);
            try {
                if (!spotsStr.empty()) p->setTotalSpots(stoi(spotsStr));
            } catch (...) {}
            newLoc = p;
        } else if (type == "SportsFacility" || type == "Sports Facility") {
            string sportStr, availStr;
            getline(ss, sportStr, '|');
            getline(ss, availStr, '|');

            SportsFacility* sf = new SportsFacility(name, x, y);
            if (!sportStr.empty()) sf->setSport(sportStr);
            if (!availStr.empty()) sf->setAvailable(availStr == "1" || availStr == "true");
            newLoc = sf;
        }

        if (newLoc) {
            newLoc->setAccessibility(ramp, elevator, entrance, restroom);
            locations.push_back(newLoc);
        }
    }

    file.close();
    return locations;
}

// ==========================================
//              REPORTS FILE
// ==========================================

void FileManager::saveReports(const vector<Report>& reports) {
    ofstream outFile(reportsFilename);
    if (!outFile) {
        cout << "Error: Could not open " << reportsFilename << " for writing.\n";
        return;
    }

    for (const auto& report : reports) {
        // Format: Location|Issue|Status
        outFile << report.getLocation() << "|"
                << report.getIssue() << "|"
                << report.getStatus() << "\n";
    }

    outFile.close();
}

vector<Report> FileManager::loadReports() {
    vector<Report> reports;
    ifstream inFile(reportsFilename);
    if (!inFile) return reports;

    string line;
    while (getline(inFile, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string location, issue, status;

        getline(ss, location, '|');
        getline(ss, issue, '|');
        getline(ss, status, '|');

        if (!location.empty() && !issue.empty()) {
            Report r(location, issue);
            if (status == "Resolved" || status == "1") {
                r.resolve();
            }
            reports.push_back(r);
        }
    }

    inFile.close();
    return reports;
}