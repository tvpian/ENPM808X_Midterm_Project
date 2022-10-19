/* Copyright 2022
 * Author(s) 
 * Tharun V. Puthanveettil, Pavan Mantripragada, Yashveer Jain
 */
#pragma once
#include <string>
#include <vector>
#include<iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/core/ocl.hpp>


Tracker::Tracker() {

}

Tracker::~Tracker() {

}

vector<cv::Rect> Tracker::init(cv::Mat& frame, std::vector<int> target_bbox) {
    return {};
}

vector<cv::Rect> Tracker::getTrackingOutput(cv::Mat& frame) {
    return {};
}


void tracker::draw_pred(cv::Mat& frame, vector<int> bbox) {

}   




    






