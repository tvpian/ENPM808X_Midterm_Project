/* Copyright 2022
 * Author(s) 
 * Tharun V. Puthanveettil, Pavan Mantripragada, Yashveer Jain
 */
#pragma once

#include<iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include<algorithm>
#include <variant>
#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/core/ocl.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "utils.hpp"
#include "obstacle.hpp"
#include "camera.hpp"
#include "detector.hpp"
#include "tracker.hpp"

class HumanTracker{
 private:
    int CurrentHumanCounts = 0;
    int humansDetectedSoFar = 0;
    int frameCount = 0;  // units are in frame count
    int detectionInterval; // units are in frame count
    int heightOfPerson;  // units are in ft.
    Detector detector;
    Camera camera;
    Tracker tracker;

 public:
    HumanTracker(std::vector<float> cameraIntrinsicsParams, cv::Mat_<float> extrinsicMatrix, int cameraID = 0,
                int detectionInterval = 50, float heightOfPerson = 6,
                std::string modelConfig = "../model_utils/yolov3.cfg",
                std::string modelWeight = "../model_utils/yolov3.weights",
                std::string classFilePath="../model_utils/coco.names");
    HumanTracker(std::vector<float> cameraIntrinsicsParams, cv::Mat_<float> extrinsicMatrix, std::string videoPath,
                int detectionInterval = 50, float heightOfPerson = 6,
                std::string modelConfig = "../model_utils/yolov3.cfg",
                std::string modelWeight = "../model_utils/yolov3.weights",
                std::string classFilePath="../model_utils/coco.names");
    float computeDistance(const cv::Rect& bbox);
    std::vector<utils::bbox> detectHuman(const cv::Mat& frame);
    cv::Mat getFrame();
    Obstacle createObstacle(float d, cv::Rect_<float> bbox);
    std::vector<Obstacle> getObstacles(cv::Mat frame);
    void display(cv::Mat frame, std::vector<utils::bbox> bboxs, std::vector<Obstacle> obstacles);
};
