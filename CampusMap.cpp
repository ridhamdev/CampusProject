#include <iostream>
#include <iomanip>
#include <vector>
#include "CampusMap.h"
#include <opencv2/opencv.hpp>

using namespace std;

CampusMap::CampusMap() {}

void CampusMap::displayMap(const vector<CampusLocation*>& locations) {
    cout << "\n======================================================\n";
    cout << "                    CAMPUS MAP                        \n";
    cout << "======================================================\n";

    // Read the image file using OpenCV. Check data/ directory first, then current directory
    cv::Mat image = cv::imread("data/Nirma_Map.png");
    

    if (image.empty()) {
        cerr << "Could not open or find the map image (data/Nirma_Map.png)!\n";
    } else {
        cout << "Displaying map window. Press any key on the image window to close.\n";
        cv::namedWindow("Campus Map", cv::WINDOW_NORMAL);
        cv::resizeWindow("Campus Map", image.rows * 3, image.cols * 3);
        cv::imshow("Campus Map", image);
        cv::waitKey(0);
        cv::destroyAllWindows();
    }

    // Location Directory
    if (!locations.empty()) {
        cout << "\nLOCATION DIRECTORY:\n";
        for (size_t i = 0; i < locations.size(); i++) {
            if (locations[i]) {
                cout << " - " << left << setw(32) << locations[i]->getName()
                     << " [" << locations[i]->getType() << "]\n";
            }
        }
        cout << "======================================================\n";
    }
}
