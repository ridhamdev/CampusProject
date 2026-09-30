#ifndef CAMPUS_MAP_H
#define CAMPUS_MAP_H

#include <vector>
#include "CampusLocation.h"

using namespace std;

class CampusMap {
public:
    CampusMap();
    static void displayMap(const vector<CampusLocation*>& locations);
};

#endif
