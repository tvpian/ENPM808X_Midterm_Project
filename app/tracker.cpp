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
    Tracker() {
        tracker = TrackerCSRT::create();
    }
    ~Tracker(){}
    vector<cv::Rect> init(cv::Mat& frame, vector<int> bbox);

    vector<cv::Rect> getTrackingOutput(cv::Mat& frame);

    void draw_pred(cv::Mat& frame, vector<int> bbox);              
}

/**
 * @brief Construct a new Tracker:: Tracker object
 * 
 */
Tracker::Tracker() {

}
/**
 * @brief Destroy the Tracker:: Tracker object
 * 
 */
Tracker::~Tracker() {

}
/**
 * @brief Initialize tracker onto the initial input frame 
 * 
 * @param frame 
 * @param bbox 
 * @return vector<cv::Rect> 
 */
vector<cv::Rect> Tracker::init(cv::Mat& frame, vector<int> bbox) {

}

/**
 * @brief 
 * 
 * @param frame 
 * @return vector<cv::Rect> 
 */
vector<cv::Rect> Tracker::getTrackingOutput(cv::Mat& frame) {

}

/**
 * @brief 
 * 
 * @param frame 
 * @param bbox 
 */
void tracker::draw_pred(cv::Mat& frame, vector<int> bbox) {

}   




    






