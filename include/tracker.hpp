/* Copyright 2022
 * Author(s) 
 * Tharun V. Puthanveettil, Pavan Mantripragada, Yashveer Jain
 */
#pragma once
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/core/ocl.hpp>

#include<iostream>



class Tracker{
private:
    Ptr<Tracker> tracker;
public:
    /**
     * @brief Constructor of Tracker class
     */
    Tracker() {
        tracker = cv::TrackerCSRT::create();
    }
    /**
     * @brief Destructor of Tracker class
     */
    ~Tracker(){}
    std::vector<cv::Rect> init(cv::Mat& frame, std::vector<int> target_bbox);

    std::vector<cv::Rect> getTrackingOutput(cv::Mat& frame);

    void draw_pred(cv::Mat& frame, std::vector<int> bbox);              
}
    






