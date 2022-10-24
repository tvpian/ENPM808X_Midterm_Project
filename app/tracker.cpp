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
#include "utils.hpp"
#include "tracker.hpp"


void Tracker::init(cv::Mat& frame, std::vector<utils::bbox> target_bboxs) {

}

std::vector<utils::bbox> Tracker::getTrackingOutput(cv::Mat& frame, std::vector<utils::bbox> target_bboxs) {
    return {};
}


void Tracker::draw_pred(cv::Mat& frame, std::vector<utils::bbox> target_bboxs) {
}






