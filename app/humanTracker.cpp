#include<iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include<algorithm>
#include <variant>
#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/core/ocl.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "utils.hpp"
#include "camera.hpp"
#include "detector.hpp"
#include "tracker.hpp"



HumanTracker::HumanTracker(float focalLength, int detectionInterval, 
                int cameraID, float heightOfPerson, std::string model_config, 
                std::string model_weight, std::string classFilePath) : camera(cameraID, focalLength) { 
        detectionInterval = detectionInterval; 
        heightOfPerson = heightOfPerson;
        detector.load_model(model_config, model_weight, classFilePath);
}


float humanTracker::computeDistance(const cv::Rect& bbox) {
    float distance = 0.0;
    float focalLength = 0.0;
    float distanceInFeet = 0.0;
    float heightOfPerson = 0.0;
    distanceInFeet = (focalLength * heightOfPerson) / bbox.height;
    return distanceInFeet;
}

std::vector<utils::bbox> humanTracker::detectHuman(const cv::Mat& frame) {
    std::vector<utils::bbox> bboxs;
    bboxs = detector.detect(frame);
    return bboxs;
}



