/* Copyright 2022
 * Author(s) 
 * Tharun V. Puthanveettil, Pavan Mantripragada, Yashveer Jain
 */
#include<iostream>

#include "opencv2/opencv.hpp"
#include "camera.hpp"

Camera::Camera(int cam_id) {
            video_cap.open(cam_id);
            if (!video_cap.isOpened()) {
                std::cout << "Error opening video stream or file" << std::endl;
                throw("Camera Not Captured");
            }
        }

cv::Mat Camera::read_frame() {
            cv::Mat frame;
            video_cap >> frame;
            if (frame.empty()) throw("Not able to read frame");
            return frame;
        }

Camera::~Camera() {
            video_cap.release();
        }
