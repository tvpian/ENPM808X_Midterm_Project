#include<iostream>

#include "opencv2/opencv.hpp"
#include "camera.hpp"


/**
 * @brief Construct a new Camera:: Camera object
 * @details intialize the video capture to read the camera streams
 */
Camera::Camera(int cam_id=0){
            video_cap(cam_id);
            if (!video_cap.isOpened()){
                std::cout << "Error opening video stream or file" << std::endl;
	            throw ("Camera Not Captured");
            }
        }

/**
 * @brief read_frame to
 * 
 * @return Camera::cv::Mat 
 */
cv::Mat Camera::read_frame(bool diplay){
            cv::Mat frame;
            video_cap >> frame;
            if (frame.empty()) throw("Not able to read frame");
            if(display)
            	cv::imshow("Frame", frame);
            char c=(char)cv::waitKey(25);
            if(c==27) throw("Terminated!");
            return frame;
        }	
