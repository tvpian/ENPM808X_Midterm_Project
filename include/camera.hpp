/* Copyright 2022
 * Author(s) 
 * Tharun V. Puthanveettil, Pavan Mantripragada, Yashveer Jain
 */
#pragma once
#include<vector>
#include <iostream>
#include "opencv2/opencv.hpp"

/**
 * @brief Camera class
 * @details Handles the camera stream
 */
class Camera {
 private:
    /** @brief video capture object to capture frames */
    cv::VideoCapture videoCapture;

 public:
        float fx;
        float fy;
        float s;
        float cx;
        float cy;
        cv::Mat_<float> K;
        cv::Mat_<float> Kinv;
        /** @brief camera extrinsics parameters */
        cv::Mat_<float> H;

        Camera(std::vector<float> cameraIntrinsicsParams, cv::Mat_<float> extrinsicMatrix, int camId = 0);
        Camera(std::vector<float> cameraIntrinsicsParams, cv::Mat_<float> extrinsicMatrix, std::string videoPath);
        /**
        * @brief read a frame 
        * 
        * @return the frame which is read
        */
        cv::Mat readFrame();

        /**
        * @brief Destroy the camera object
        * @details release the video capture stream 
        */
        ~Camera();

        void setCameraExtrinsics(cv::Mat_<float> extrinsicMatrix);

        void setCameraIntrinsics();
};
