#ifndef USER_H
#define USER_H

#include <string>
using namespace std;
class User {
protected:
    string name;
    string role;

public:
    User(string n, string r);
    virtual ~User();

    virtual string getName() const;
    virtual string getRole() const;

    virtual void showMenu() = 0;
};

#endif
