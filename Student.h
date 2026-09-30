#ifndef STUDENT_H
#define STUDENT_H

#include "User.h"
#include "Report.h"
#include <vector>

using namespace std;

class Student : public User {
private:
    string studentID;
    string course;
    int yearOfStudy;

public:
    Student(string n, string r, string id, string c, int year);

    void displayDetails() const;

    void setStudentID(string id);
    void setCourse(string c);
    void setYearOfStudy(int year);

    void showMenu();

    void createReport(vector<Report>& reports);

    string getName() const override {
        return name;
    }
    string getRole() const override {
        return role;
    }
    string getStudentID() const {
        return studentID;
    }
    string getCourse() const {
        return course;
    }
    int getYearOfStudy() const {
        return yearOfStudy;
    }
};

#endif