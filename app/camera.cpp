/* Copyright 2022
 * Author(s) 
 * Tharun V. Puthanveettil, Pavan Mantripragada, Yashveer Jain
 */
#include<iostream>
#include<vector>
#include "opencv2/opencv.hpp"
#include "camera.hpp"

Camera::Camera(std::vector<float> cameraIntrinsicsParams, cv::Mat_<float> extrinsicMatrix, int camId
        ): fx{cameraIntrinsicsParams[0]}, fy{cameraIntrinsicsParams[1]}, s{cameraIntrinsicsParams[2]}, cx{cameraIntrinsicsParams[3]}, cy{cameraIntrinsicsParams[4]} {
            video_cap.open(camId);
            if (!video_cap.isOpened()) {
                std::cout << "Error opening video stream or file" << std::endl;
                throw("Camera Not Captured");
            }
            setCameraIntrinsics();
            setCameraExtrinsics(extrinsicMatrix);
        }

Camera::Camera(std::vector<float> cameraIntrinsicsParams, cv::Mat_<float> extrinsicMatrix, std::string videoPath
        ): fx{cameraIntrinsicsParams[0]}, fy{cameraIntrinsicsParams[1]}, s{cameraIntrinsicsParams[2]}, cx{cameraIntrinsicsParams[3]}, cy{cameraIntrinsicsParams[4]} {
            video_cap.open(videoPath);
            if (!video_cap.isOpened()) {
                std::cout << "Error opening video stream or file" << std::endl;
                throw("Camera Not Captured");
            }
            setCameraIntrinsics();
            setCameraExtrinsics(extrinsicMatrix);
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

void Camera::setCameraExtrinsics(cv::Mat_<float> extrinsicMatrix){
    H = extrinsicMatrix;
}

void Camera::setCameraIntrinsics(){
    float params[]={fx, s, cx, 0, fy, cy, 0, 0, 1};
    cv::Mat intrinsicMatrix(3,3,CV_32F,params);
    K = intrinsicMatrix;
    Kinv = intrinsicMatrix.inv();
}
