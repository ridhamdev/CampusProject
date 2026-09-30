#ifndef REPORT_H
#define REPORT_H

#include <string>
using namespace std;
class Report {
private:
    string location;
    string issue;
    string status;

public:
    Report(string locationName, string issueText);

    void displayReport() const;
    void resolve();

    std::string getLocation() const;
    std::string getIssue() const;
    std::string getStatus() const;
};

#endif
