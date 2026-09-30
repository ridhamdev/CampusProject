#include <iostream>
#include "Admin.h"

using namespace std;

Admin::Admin(string n, string r, string p)
    : User(n, r), password(p) {
}
string Admin::getName() const {
    return name;
}
void Admin::showMenu() {
    cout << "\n================ ADMIN ================\n";
    cout << "1. View Campus Map\n";
    cout << "2. View All Locations\n";
    cout << "3. Add Location\n";
    cout << "4. Update Location\n";
    cout << "5. Update Accessibility Information\n";
    cout << "6. View Student Reports\n";
    cout << "7. Resolve Report\n";
    cout << "8. Save Data\n";
    cout << "9. Exit\n";
}

void Admin::viewReports(vector<Report>& reports) {
    cout << "\n========== PENDING STUDENT REPORTS ==========\n";

    if (reports.empty()) {
        cout << "No pending reports available.\n";
        return;
    }

    for (size_t i = 0; i < reports.size(); i++) {
        cout << "\nReport #" << (i + 1) << "\n";
        cout << "--------------------------------\n";
        reports[i].displayReport();
    }
}

void Admin::resolveReport(vector<Report>& reports, int index) {
    if (index < 0 || index >= static_cast<int>(reports.size())) {
        cout << "Invalid report number.\n";
        return;
    }

    cout << "Resolving report #" << (index + 1) << " (" << reports[index].getLocation() << ": " << reports[index].getIssue() << ")...\n";
    reports.erase(reports.begin() + index);
    cout << "Report marked as resolved and removed from pending reports.\n";
}