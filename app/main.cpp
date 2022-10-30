/** Copyright [2022]
 * @Authors <Tharun V. Puthanveettil, Pavan Mantripragada, Yashveer Jain>
**/
#include <iostream>
#include "utils.hpp"
#include "camera.hpp"
#include "detector.hpp"
#include "tracker.hpp"
#include "humanTracker.hpp"
#include "obstacle.hpp"


int main() {
    float data[16] = { 0, 0, -1, 0, 1, 0, 0, 0.5, 0, -1, 0, 0.5, 0, 0, 0, 1 };
    cv::Mat cameraExtrinsicsMatrix = cv::Mat(4, 4, CV_32F, data); 
    std::vector<float> cameraIntrinsicsParams = {300, 300, 0, 360, 200};
    HumanTracker humanTracker(cameraIntrinsicsParams, cameraExtrinsicsMatrix, 0);
    while(true)
    {   
        cv::Mat frame;
        try{
            frame = humanTracker.getFrame();
        }
        catch(...){
            cout<<" camera unable to read frame Error";
            break;
        }
        std::vector<Obstacle> obstacles = humanTracker.getObstacles(frame);
        char c = (char)cv::waitKey(1);
        if( c == 27 ) break;
    }
    return 0;
}