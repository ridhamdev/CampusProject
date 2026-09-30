#include "User.h"

User::User(string n, string r) : name(n), role(r) {}

User::~User() {}

string User::getName() const {
    return name;
}

string User::getRole() const {
    return role;
}