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
#include "camera.hpp"
#include "detector.hpp"
#include "tracker.hpp"

class HumanTracker{
 private:
    int CurrentHumanCounts = 0;
    int humansDetectedSoFar = 0;
    Detector detector();
    Camera camera();
    Tracker tracker();

 public:
    float computeDistance(const cv::Rect& bbox);
    std::vector<cv::Rect> detectHuman(const cv::Mat& frame);
    cv::Mat getImage();
    cv::Rect trackHuman(cv::Rect& bbox);
};
