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


void load_model(string model_Config, string model_Weights){
}


void Detector::preprocessing(cv::Mat& frame){ 
}


void Detector::drawPred(int classID, float conf, int left, int top, int right,
int bottom, Mat& frame){
} 


std::vector<std::variant<int,float,cv::Rect>> Detector::detect(cv::Mat frame){
    return {}
}



vector<String> Detector::getOutputsNames(const Net& net) {
    return {};
}


std::vector<std::variant<int,float,cv::Rect>> Detector::postprocess(Mat& frame, const vector<Mat>& outs) {
    return {};
}


