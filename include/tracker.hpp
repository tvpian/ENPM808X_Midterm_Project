/* Copyright 2022
 * Author(s) 
 * Tharun V. Puthanveettil, Pavan Mantripragada, Yashveer Jain
 */
#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/core/ocl.hpp>

using namespace std;

/**
 * @brief Tracker classs
 * 
 */
class Tracker {
 private:
/**
   * @Brief  Pointer to the tracker object
   */
    cv::Ptr<cv::Tracker> tracker;

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
    ~Tracker() {}
    /**
     * @brief Initialize the tracker on the initial frame
     * 
     * @param frame input frame  
     * @param target_bbox initial bounding box 
     */    

    std::vector<cv::Rect> init(cv::Mat& frame, std::vector<int> target_bbox);
    /**
     * @brief Extract the bounding box of tracker target in next frame
     * 
     * @param frame Input image frame  
     */
    std::vector<cv::Rect> getTrackingOutput(cv::Mat& frame);

    /**
     * @brief Draw bounding box for the tracked target
     * 
     * @param frame Input image frame
     * @param bbox Detected bounding box coordinate from previous frame 
     */
    void draw_pred(cv::Mat& frame, std::vector<int> bbox);
};





