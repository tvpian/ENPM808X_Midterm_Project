/* Copyright 2022
 * Author(s) 
 * Tharun V. Puthanveettil, Pavan Mantripragada, Yashveer Jain
 */
#include <fstream>
#include <sstream>
#include <iostream>

#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "include/detector.hpp"

void Detector::load_model(std::string model_Config, std::string model_Weights) {
}


void Detector::preprocessing(cv::Mat& frame) {
}


void Detector::drawPred(int classID, float conf, int left, int top, int right,
int bottom, cv::Mat& frame) {
}


std::vector<cv::Rect>  Detector::detect(cv::Mat frame) {
    return {};
}



std::vector<std::string> Detector::getOutputnames(const cv::dnn::Net& net) {
    return {};
}


std::vector<cv::Rect> Detector::postprocessing(cv::Mat& frame, const std::vector<cv::Mat>& outs) {
    return {};
}



