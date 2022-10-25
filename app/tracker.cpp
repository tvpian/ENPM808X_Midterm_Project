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
    cv::RNG rng(0);
    for(utils::bbox target_bbox : target_bboxs){
        trackers->add(cv::TrackerCSRT::create(), frame, cv::Rect2d(target_bbox.box));
        colors.push_back(cv::Scalar(rng.uniform(0,255), rng.uniform(0, 255), rng.uniform(0, 255)));
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
    for(unsigned i=0; i<target_bboxs.size(); i++){
        cv::rectangle(frame, cv::Rect2d(target_bboxs[i].box), colors[i], 2, 1);
    }
}






