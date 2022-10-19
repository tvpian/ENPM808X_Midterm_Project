#pragme once

#include<iostream>
#include "opencv2/opencv.hpp"

/**
 * @brief Camera class
 * @details Handles the camera stream
 */
class Camera
{
    private:
         cv::VideoCapture video_cap;
    public:
        Camera();
        cv::Mat read_frame();
        ~Camera(){
        }
}