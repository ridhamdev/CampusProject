#include <iostream>
#include "Student.h"

using namespace std;

Student::Student(string n, string r, string id, string c, int year)
    : User(n, r), studentID(id), course(c), yearOfStudy(year) {
}

void Student::displayDetails() const {

    cout << "\n========================================\n";
    cout << "            STUDENT DETAILS             \n";
    cout << "========================================\n";

    cout << "Name: " << name << "\n";
    cout << "Role: " << role << "\n";
    cout << "Student ID: " << studentID << "\n";
    cout << "Course: " << course << "\n";
    cout << "Year of Study: " << yearOfStudy << "\n";
}

void Student::setStudentID(string id) {
    studentID = id;
}

void Student::setCourse(string c) {
    course = c;
}

void Student::setYearOfStudy(int year) {
    yearOfStudy = year;
}

void Student::showMenu() {

    cout << "\n================ STUDENT ================\n";

    cout << "1. View Campus Map\n";
    cout << "2. Search Location\n";
    cout << "3. View Location Details\n";
    cout << "4. View Accessibility Information\n";
    cout << "5. Report an Issue\n";
    cout << "6. Back\n";
}

void Student::createReport(vector<Report>& reports) {
    string location;
    string issue;

    cout << "\n--- Report an Accessibility Issue ---\n";
    cout << "Enter location name: ";
    getline(cin, location);
    cout << "Describe the issue: ";
    getline(cin, issue);

    if (location.empty() || issue.empty()) {
        cout << "Location and issue cannot be empty. Report cancelled.\n";
        return;
    }

    Report newReport(location, issue);
    reports.push_back(newReport);

    cout << "\nReport submitted successfully!\n";
}