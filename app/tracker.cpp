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
    for(utils::bbox target_bbox : target_bboxs){
        trackers->add(cv::TrackerCSRT::create(), frame, cv::Rect2d(target_bbox.box));
    }
}

std::vector<utils::bbox> Tracker::getTrackingOutput(cv::Mat& frame) {
    trackers->update(frame);
    std::vector<utils::bbox> updated_bboxs;
    for(auto tracked_object : trackers->getObjects()){
        updated_bboxs.push_back({0, 100.0, cv::Rect(tracked_object)});
    }
    return updated_bboxs;
}


void Tracker::draw_pred(cv::Mat& frame, std::vector<utils::bbox> target_bboxs) {
}






