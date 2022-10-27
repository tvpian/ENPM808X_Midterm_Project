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
    cv::VideoCapture video_cap;

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

        /**
        * @brief Construct a new camera object
        * @details intialize the video capture to read the camera streams
        *
        * @param cam_id device id to select a camera
        */
        explicit Camera(int cam_id = 0, std::vector<float> cameraIntrinsicsParams = {1920.0, 1920.0, 0.0, 960.0, 540.0});

        /**
        * @brief read a frame 
        * 
        * @return the frame which is read
        */
        cv::Mat read_frame();

        /**
        * @brief Destroy the camera object
        * @details release the video capture stream 
        */
        ~Camera();

        void setCameraExtrinsics(cv::Mat_<float> extrinsicMatrix);

        void setCameraIntrinsics();
};
