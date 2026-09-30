#include <iostream>
#include <vector>
#include <string>
#include <limits>

#include "User.h"
#include "Student.h"
#include "Admin.h"

#include "CampusLocation.h"
#include "CampusMap.h"
#include "Canteen.h"
#include "Gate.h"
#include "Hostel.h"
#include "LectureBuilding.h"
#include "library.h"
#include "Parking.h"
#include "sportsFacility.h"
#include "FileManager.h"

using namespace std;

// Helper function prototypes
void displayAllLocations(const vector<CampusLocation*>& locations);
void searchLocation(const vector<CampusLocation*>& locations);
void displayAccessibilityInfo(const vector<CampusLocation*>& locations);
void addLocationMenu(vector<CampusLocation*>& locations, FileManager& fileManager);
void updateLocationMenu(vector<CampusLocation*>& locations, FileManager& fileManager);
void updateAccessibilityMenu(vector<CampusLocation*>& locations, FileManager& fileManager);
void enrollStudentPage(vector<User*>& users, FileManager& fileManager);
void cleanUpMemory(vector<CampusLocation*>& locations, vector<User*>& users);

int main() {
    FileManager fileManager("data/User.txt", "data/locations.txt", "data/reports.txt");

    // Load data from files
    vector<CampusLocation*> locations = fileManager.loadLocations();
    vector<User*> users = fileManager.loadUsers();
    vector<Report> reports = fileManager.loadReports();

    // If no admin exists in users file, create default admin
    bool hasAdmin = false;
    for (const auto* u : users) {
        if (dynamic_cast<const Admin*>(u)) {
            hasAdmin = true;
            break;
        }
    }
    if (!hasAdmin) {
        users.push_back(new Admin("Admin", "Admin", "admin123"));
        fileManager.saveUsers(users);
    }

    int mainChoice = 0;

    while (true) {
        cout << "\n========================================\n";
        cout << "     CAMPUS ACCESSIBILITY SYSTEM        \n";
        cout << "========================================\n";
        cout << "1. Login as Student\n";
        cout << "2. Enroll as New Student\n";
        cout << "3. Login as Admin\n";
        cout << "4. Exit\n";
        cout << "Enter choice (1-4): ";

        if (!(cin >> mainChoice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        if (mainChoice == 4) {
            cout << "\nSaving data and exiting application. Goodbye!\n";
            fileManager.saveLocations(locations);
            fileManager.saveUsers(users);
            fileManager.saveReports(reports);
            break;
        }

        if (mainChoice == 2) {
            // Student Enrollment Page
            enrollStudentPage(users, fileManager);
        }
        else if (mainChoice == 1) {
            // Student Login
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            string studentId;
            cout << "\n========================================\n";
            cout << "             STUDENT LOGIN              \n";
            cout << "========================================\n";
            cout << "Enter Student ID: ";
            getline(cin, studentId);

            Student* currentStudent = nullptr;
            for (auto* u : users) {
                Student* s = dynamic_cast<Student*>(u);
                if (s && s->getStudentID() == studentId) {
                    currentStudent = s;
                    break;
                }
            }

            if (!currentStudent) {
                cout << "\n[!] No student found with ID '" << studentId << "'.\n";
                cout << "Would you like to enroll as a new student? (y/n): ";
                char enrollChoice;
                cin >> enrollChoice;
                if (enrollChoice == 'y' || enrollChoice == 'Y') {
                    enrollStudentPage(users, fileManager);
                }
                continue;
            }

            cout << "\nWelcome back, " << currentStudent->getName()
                 << " (" << currentStudent->getCourse()
                 << ", Year " << currentStudent->getYearOfStudy() << ")!\n";

            int subChoice = 0;
            while (subChoice != 6) {
                currentStudent->showMenu();
                cout << "Enter option (1-6): ";
                if (!(cin >> subChoice)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid choice. Try again.\n";
                    continue;
                }

                switch (subChoice) {
                    case 1:
                        CampusMap::displayMap(locations);
                        break;
                    case 2:
                        searchLocation(locations);
                        break;
                    case 3:
                        displayAllLocations(locations);
                        break;
                    case 4:
                        displayAccessibilityInfo(locations);
                        break;
                    case 5:
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        currentStudent->createReport(reports);
                        fileManager.saveReports(reports); // Persist newly created report
                        break;
                    case 6:
                        cout << "Logging out...\n";
                        break;
                    default:
                        cout << "Invalid choice. Try again.\n";
                }
            }
        }
        else if (mainChoice == 3) {
            // Admin Login
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            string adminName, adminPassword;
            cout << "\n========================================\n";
            cout << "              ADMIN LOGIN               \n";
            cout << "========================================\n";
            cout << "Enter Admin Username: ";
            getline(cin, adminName);
            cout << "Enter Password: ";
            getline(cin, adminPassword);

            Admin* currentAdmin = nullptr;
            for (auto* u : users) {
                Admin* a = dynamic_cast<Admin*>(u);
                if (a && a->getName() == adminName && a->getPassword() == adminPassword) {
                    currentAdmin = a;
                    break;
                }
            }

            if (!currentAdmin) {
                cout << "\n[!] Invalid Admin username or password.\n";
                continue;
            }

            cout << "\nAdmin access granted! Welcome, " << currentAdmin->getName() << ".\n";

            int subChoice = 0;
            while (subChoice != 9) {
                currentAdmin->showMenu();
                cout << "Enter option (1-9): ";
                if (!(cin >> subChoice)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid choice.\n";
                    continue;
                }

                switch (subChoice) {
                    case 1:
                        CampusMap::displayMap(locations);
                        break;
                    case 2:
                        displayAllLocations(locations);
                        break;
                    case 3:
                        addLocationMenu(locations, fileManager);
                        break;
                    case 4:
                        updateLocationMenu(locations, fileManager);
                        break;
                    case 5:
                        updateAccessibilityMenu(locations, fileManager);
                        break;
                    case 6:
                        currentAdmin->viewReports(reports);
                        break;
                    case 7: {
                        // Resolve Report - once cleared it is removed from the file
                        if (reports.empty()) {
                            cout << "\nNo pending reports to resolve.\n";
                        } else {
                            currentAdmin->viewReports(reports);
                            cout << "\nEnter report number to resolve and clear (1-" << reports.size() << "): ";
                            int idx;
                            if (cin >> idx) {
                                currentAdmin->resolveReport(reports, idx - 1);
                                fileManager.saveReports(reports); // Immediate update: cleared report removed from file
                                cout << "Reports file updated successfully. Cleared report removed from file.\n";
                            } else {
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                cout << "Invalid report number.\n";
                            }
                        }
                        break;
                    }
                    case 8:
                        fileManager.saveLocations(locations);
                        fileManager.saveUsers(users);
                        fileManager.saveReports(reports);
                        cout << "\nAll data (Locations, Users, Reports) saved to files successfully.\n";
                        break;
                    case 9:
                        cout << "Exiting Admin panel...\n";
                        break;
                    default:
                        cout << "Invalid choice.\n";
                }
            }
        } else {
            cout << "Invalid choice. Please enter 1, 2, 3, or 4.\n";
        }
    }

    // Deallocate dynamically allocated memory
    cleanUpMemory(locations, users);
    return 0;
}

// ==========================================
//           STUDENT ENROLLMENT PAGE
// ==========================================

void enrollStudentPage(vector<User*>& users, FileManager& fileManager) {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string name, id, course;
    int year = 1;

    cout << "\n========================================\n";
    cout << "         NEW STUDENT ENROLLMENT         \n";
    cout << "========================================\n";

    cout << "Enter Full Name: ";
    getline(cin, name);
    if (name.empty()) {
        cout << "Name cannot be empty. Enrollment cancelled.\n";
        return;
    }

    cout << "Enter Student ID (e.g. S103): ";
    getline(cin, id);
    if (id.empty()) {
        cout << "Student ID cannot be empty. Enrollment cancelled.\n";
        return;
    }

    // Check if ID already exists
    for (const auto* u : users) {
        const Student* s = dynamic_cast<const Student*>(u);
        if (s && s->getStudentID() == id) {
            cout << "\n[!] Error: A student with ID '" << id << "' is already enrolled.\n";
            cout << "Please log in using your ID or contact admin.\n";
            return;
        }
    }

    cout << "Enter Course (e.g. Computer Science): ";
    getline(cin, course);
    if (course.empty()) course = "General";

    cout << "Enter Year of Study (1-5): ";
    if (!(cin >> year) || year < 1 || year > 6) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        year = 1;
        cout << "Invalid year. Defaulting to Year 1.\n";
    }

    // Create new student and add to system
    Student* newStudent = new Student(name, "Student", id, course, year);
    users.push_back(newStudent);

    // Save users file
    fileManager.saveUsers(users);

    cout << "\n========================================\n";
    cout << "  ENROLLMENT SUCCESSFUL!               \n";
    cout << "========================================\n";
    cout << "Welcome, " << name << "!\n";
    cout << "Your Student ID is: " << id << "\n";
    cout << "You can now log in anytime using your Student ID.\n";
}

// ==========================================
//          CAMPUS LOCATION HELPERS
// ==========================================

void displayAllLocations(const vector<CampusLocation*>& locations) {
    if (locations.empty()) {
        cout << "\nNo locations registered in the system.\n";
        return;
    }
    for (const auto* loc : locations) {
        if (loc) loc->displayDetails();
    }
}

void searchLocation(const vector<CampusLocation*>& locations) {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string searchName;
    cout << "\nEnter location name to search: ";
    getline(cin, searchName);

    bool found = false;
    for (const auto* loc : locations) {
        if (!loc) continue;

        // Substring / case search or exact match
        if (loc->getName() == searchName || loc->getName().find(searchName) != string::npos) {
            loc->displayDetails();
            loc->displayAccessibility();
            found = true;
        }
    }
    if (!found) {
        cout << "\nLocation '" << searchName << "' not found.\n";
    }
}

void displayAccessibilityInfo(const vector<CampusLocation*>& locations) {
    if (locations.empty()) {
        cout << "\nNo locations registered.\n";
        return;
    }
    for (const auto* loc : locations) {
        if (loc) loc->displayAccessibility();
    }
}

void addLocationMenu(vector<CampusLocation*>& locations, FileManager& fileManager) {
    cout << "\n========================================\n";
    cout << "           ADD NEW LOCATION             \n";
    cout << "========================================\n";
    cout << "1. Canteen\n";
    cout << "2. Campus Gate\n";
    cout << "3. Hostel\n";
    cout << "4. Lecture Building\n";
    cout << "5. Library\n";
    cout << "6. Parking Area\n";
    cout << "7. Sports Facility\n";
    cout << "Enter location type (1-7): ";

    int choice;
    if (!(cin >> choice) || choice < 1 || choice > 7) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid choice. Operation cancelled.\n";
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string name;
    int x, y;

    cout << "Enter Location Name: ";
    getline(cin, name);
    cout << "Enter X Coordinate (0-100): ";
    cin >> x;
    cout << "Enter Y Coordinate (0-100): ";
    cin >> y;

    // Accessibility features
    int rampInput, elevInput, entInput, restInput;
    cout << "Has Ramp? (1=Yes, 0=No): ";
    cin >> rampInput;
    cout << "Has Elevator? (1=Yes, 0=No): ";
    cin >> elevInput;
    cout << "Has Accessible Entrance? (1=Yes, 0=No): ";
    cin >> entInput;
    cout << "Has Accessible Restroom? (1=Yes, 0=No): ";
    cin >> restInput;

    CampusLocation* newLoc = nullptr;

    if (choice == 1) {
        int cap;
        string openTime, closeTime;
        cout << "Enter Seating Capacity: ";
        cin >> cap;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter Opening Time (e.g. 08:00 AM): ";
        getline(cin, openTime);
        cout << "Enter Closing Time (e.g. 09:00 PM): ";
        getline(cin, closeTime);
        newLoc = new Canteen(name, cap, openTime, closeTime, x, y);
    } else if (choice == 2) {
        newLoc = new Gate(name, x, y);
    } else if (choice == 3) {
        int rooms, cap;
        cout << "Enter Room Count: ";
        cin >> rooms;
        cout << "Enter Total Capacity: ";
        cin >> cap;
        Hostel* h = new Hostel(name, x, y);
        h->setRoomCount(rooms);
        h->setCapacity(cap);
        h->setWarden(true);
        h->setAccessibleEntrance(entInput == 1);
        newLoc = h;
    } else if (choice == 4) {
        int floors, classrooms, labs, lifts;
        cout << "Enter Floor Count: ";
        cin >> floors;
        cout << "Enter Classroom Count: ";
        cin >> classrooms;
        cout << "Enter Lab Count: ";
        cin >> labs;
        cout << "Enter Lift Count: ";
        cin >> lifts;
        newLoc = new LectureBuilding(name, x, y, floors, classrooms, labs, lifts);
    } else if (choice == 5) {
        int floors, classrooms;
        string blockName;
        cout << "Enter Floor Count: ";
        cin >> floors;
        cout << "Enter Reading Rooms/Classrooms: ";
        cin >> classrooms;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter Block Name (e.g. Block C): ";
        getline(cin, blockName);
        newLoc = new Library(name, x, y, floors, classrooms, true, elevInput == 1, blockName);
    } else if (choice == 6) {
        string pType;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter Parking Type (e.g. Two-Wheeler / Four-Wheeler): ";
        getline(cin, pType);
        int spots;
        cout << "Enter Total Parking Spots: ";
        cin >> spots;
        Parking* p = new Parking(name, pType, x, y);
        p->setTotalSpots(spots);
        newLoc = p;
    } else if (choice == 7) {
        string sportName;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter Sport (e.g. Basketball, Badminton): ";
        getline(cin, sportName);
        SportsFacility* sf = new SportsFacility(name, x, y);
        sf->setSport(sportName);
        sf->setAvailable(true);
        newLoc = sf;
    }

    if (newLoc) {
        newLoc->setAccessibility(rampInput == 1, elevInput == 1, entInput == 1, restInput == 1);
        locations.push_back(newLoc);
        fileManager.saveLocations(locations);
        cout << "\nLocation '" << name << "' added and saved successfully!\n";
    }
}

void updateLocationMenu(vector<CampusLocation*>& locations, FileManager& fileManager) {
    if (locations.empty()) {
        cout << "\nNo locations available to update.\n";
        return;
    }

    cout << "\n========================================\n";
    cout << "         UPDATE LOCATION DETAILS        \n";
    cout << "========================================\n";
    for (size_t i = 0; i < locations.size(); i++) {
        cout << (i + 1) << ". " << locations[i]->getName()
             << " (" << locations[i]->getType() << ")\n";
    }

    cout << "Select location to update (1-" << locations.size() << "): ";
    int idx;
    if (!(cin >> idx) || idx < 1 || idx > static_cast<int>(locations.size())) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid selection.\n";
        return;
    }

    CampusLocation* loc = locations[idx - 1];
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string newName;
    int newX, newY;

    cout << "Current Name: " << loc->getName() << "\n";
    cout << "Enter New Name (leave blank to keep current): ";
    getline(cin, newName);
    if (!newName.empty()) {
        loc->setName(newName);
    }

    cout << "Current Coordinates: (" << loc->getX() << ", " << loc->getY() << ")\n";
    cout << "Enter New X Coordinate: ";
    cin >> newX;
    cout << "Enter New Y Coordinate: ";
    cin >> newY;
    loc->setCoordinates(newX, newY);

    fileManager.saveLocations(locations);
    cout << "\nLocation details updated and saved successfully!\n";
}

void updateAccessibilityMenu(vector<CampusLocation*>& locations, FileManager& fileManager) {
    if (locations.empty()) {
        cout << "\nNo locations available to update.\n";
        return;
    }

    cout << "\n========================================\n";
    cout << "     UPDATE ACCESSIBILITY SETTINGS      \n";
    cout << "========================================\n";
    for (size_t i = 0; i < locations.size(); i++) {
        cout << (i + 1) << ". " << locations[i]->getName() << "\n";
    }

    cout << "Select location (1-" << locations.size() << "): ";
    int idx;
    if (!(cin >> idx) || idx < 1 || idx > static_cast<int>(locations.size())) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid selection.\n";
        return;
    }

    CampusLocation* loc = locations[idx - 1];
    int ramp, elev, ent, rest;

    cout << "\nUpdating Accessibility for: " << loc->getName() << "\n";
    cout << "Ramp Available? (1=Yes, 0=No): ";
    cin >> ramp;
    cout << "Elevator Available? (1=Yes, 0=No): ";
    cin >> elev;
    cout << "Accessible Entrance? (1=Yes, 0=No): ";
    cin >> ent;
    cout << "Accessible Restroom? (1=Yes, 0=No): ";
    cin >> rest;

    loc->setAccessibility(ramp == 1, elev == 1, ent == 1, rest == 1);
    fileManager.saveLocations(locations);
    cout << "\nAccessibility settings updated and saved successfully!\n";
}

void cleanUpMemory(vector<CampusLocation*>& locations, vector<User*>& users) {
    for (auto* loc : locations) {
        delete loc;
    }
    locations.clear();

    for (auto* u : users) {
        delete u;
    }
    users.clear();
}