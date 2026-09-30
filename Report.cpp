#include <iostream>
#include "Report.h"

using namespace std;

Report::Report(string locationName, string issueText)
    : location(locationName), issue(issueText), status("Pending") {
}

void Report::displayReport() const {
    cout << "Location: " << location << "\n";
    cout << "Issue: " << issue << "\n";
    cout << "Status: " << status << "\n";
}

void Report::resolve() {
    status = "Resolved";
}

string Report::getLocation() const {
    return location;
}

string Report::getIssue() const {
    return issue;
}

string Report::getStatus() const {
    return status;
}
