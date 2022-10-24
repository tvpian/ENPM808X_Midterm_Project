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
#include "detector.hpp"

void Detector::load_model(std::string model_Config, std::string model_Weights, std::string device) {
        net = cv::dnn::readNetFromDarknet(model_Config, model_Weights);
        if (device == "cpu") {
            std::cout << "Using CPU device" << std::endl;
            net.setPreferableBackend(cv::dnn::DNN_TARGET_CPU);
        } else if (device == "gpu") {
            std::cout << "Using GPU device" << std::endl;
            net.setPreferableBackend(cv::dnn::DNN_BACKEND_CUDA);
            net.setPreferableTarget(cv::dnn::DNN_TARGET_CUDA);
        }
}


cv::Mat Detector::preprocessing(cv::Mat& frame) {
    cv::Mat blob;
    cv::dnn::blobFromImage(frame, blob, 1/255.0, cv::Size(inputWidth, inputHeight), cv::Scalar(0,0,0), true, false); 
    return blob;
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



