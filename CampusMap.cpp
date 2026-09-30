#include <iostream>
#include <iomanip>
#include "CampusMap.h"

using namespace std;

CampusMap::CampusMap() {}

void CampusMap::displayMap(const vector<CampusLocation*>& locations) {
    cout << "\n======================================================\n";
    cout << "                    CAMPUS MAP                        \n";
    cout << "======================================================\n";

    if (locations.empty()) {
        cout << "No locations available to map.\n";
        return;
    }

    // Grid representation (Width: 40 cols, Height: 15 rows)
    const int GRID_W = 40;
    const int GRID_H = 15;
    char grid[GRID_H][GRID_W];

    for (int r = 0; r < GRID_H; r++) {
        for (int c = 0; c < GRID_W; c++) {
            grid[r][c] = '.';
        }
    }

    // Map locations onto grid
    for (const auto* loc : locations) {
        int x = loc->getX();
        int y = loc->getY();

        // Scale coordinates to fit into grid (assume max campus span 100x100)
        int col = (x * (GRID_W - 1)) / 100;
        int row = (y * (GRID_H - 1)) / 100;

        if (col < 0) col = 0;
        if (col >= GRID_W) col = GRID_W - 1;
        if (row < 0) row = 0;
        if (row >= GRID_H) row = GRID_H - 1;

        string type = loc->getType();
        char symbol = 'O';
        if (type == "Canteen") symbol = 'C';
        else if (type == "Gate") symbol = 'G';
        else if (type == "Hostel") symbol = 'H';
        else if (type == "LectureBuilding") symbol = 'L';
        else if (type == "Library") symbol = 'B';
        else if (type == "Parking") symbol = 'P';
        else if (type == "SportsFacility") symbol = 'S';

        grid[row][col] = symbol;
    }

    // Print Grid
    cout << "     0" << setw(GRID_W - 1) << "100 (X)\n";
    cout << "   +" << string(GRID_W, '-') << "+\n";
    for (int r = 0; r < GRID_H; r++) {
        if (r == 0) cout << " 0 |";
        else if (r == GRID_H - 1) cout << "100|";
        else cout << "   |";

        for (int c = 0; c < GRID_W; c++) {
            cout << grid[r][c];
        }
        cout << "|\n";
    }
    cout << "   +" << string(GRID_W, '-') << "+\n";
    cout << " (Y)\n\n";

    // Legend
    cout << "LEGEND:\n";
    cout << " [C] Canteen         [G] Campus Gate     [H] Hostel\n";
    cout << " [L] Lecture Block   [B] Library         [P] Parking\n";
    cout << " [S] Sports Facility [.] Open Walkway / Lawn\n";
    cout << "------------------------------------------------------\n";
    cout << "LOCATION DIRECTORY:\n";
    for (size_t i = 0; i < locations.size(); i++) {
        cout << " - " << left << setw(28) << locations[i]->getName()
             << " [" << locations[i]->getType() << "] at ("
             << locations[i]->getX() << ", " << locations[i]->getY() << ")\n";
    }
    cout << "======================================================\n";
}
