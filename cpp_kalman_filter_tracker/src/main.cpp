#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <thread>

#include "Tracker.h"

std::mutex cout_mtx_;

std::vector<std::vector<float>> readDataFile(std::string filepath){
    std::vector<std::vector<float>> data;
    std::ifstream file(filepath);
    std::string line;
    while(std::getline(file, line))
    {
        std::vector<float>   lineData;
        std::stringstream  lineStream(line);
        float value;
        while(lineStream >> value)
        {
            lineData.push_back(value);
        }
        data.push_back(lineData);
    }
    return data;
}

int main(){
    // Open connection to file, read read detections into 'data' vector
    std::string filepath = "../data/test_data4.txt";
    std::vector<std::vector<float>> data = readDataFile(filepath);

    // Instantiate TrackerManager
    TrackerManager manager;

    // Main loop
    int idx = 0;
    while (!manager._shutdown){

        // 1. Read in frame detections
        std::vector<std::vector<float>> frameDetections;
        int numDetections = data[idx].size() / 4;
        std::cout<<"Frame idx:"<< idx << " numDetections:"<< numDetections <<std::endl;
        for (int n = 0; n < numDetections; ++n){
            std::vector<float> det;
            for (int j = 0; j < 4; ++j){
                det.push_back(data[idx][(4*n) + j]);
            }
            frameDetections.push_back(det);
        }
        manager.setNewDetections(idx,frameDetections);
        
        // 2. Associate detections (measurements) to existing tracks
        manager.associate();
        // Modifies _newDetections, only unassociated new detections remain

        // 3. Create new tracks from unassociated measurements
        manager.createNewTracks();

        // 5. Update visuals 
        //TBD//

        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        std::cout<<" ###########################END OF MAIN LOOP "<<idx<< std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        
        ++idx;
    }
}