#ifndef ADMIN_H
#define ADMIN_H

#include "Report.h"
#include "User.h"
#include <vector>

using namespace std;

class Admin : public User {
private:
  string password;

public:
  Admin(string n, string r, string p);

  void showMenu() override;
  string getName() const override;
  void viewReports(vector<Report> &reports);
  void resolveReport(vector<Report> &reports, int index);
  string getRole() const override { return role; }
  string getPassword() const { return password; }
};

#endif