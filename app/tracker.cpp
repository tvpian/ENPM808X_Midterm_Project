/* Copyright 2022
 * Author(s) 
 * Tharun V. Puthanveettil, Pavan Mantripragada, Yashveer Jain
 */

#include <string>
#include <vector>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/core/ocl.hpp>
#include "tracker.hpp"


std::vector<cv::Rect> Tracker::init(cv::Mat& frame, std::vector<int> target_bbox) {
    return {};
}

std::vector<cv::Rect> Tracker::getTrackingOutput(cv::Mat& frame) {
    return {};
}


void Tracker::draw_pred(cv::Mat& frame, std::vector<int> bbox) {
}






