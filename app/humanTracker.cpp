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
#include "obstacle.hpp"
#include "camera.hpp"
#include "detector.hpp"
#include "tracker.hpp"
#include "humanTracker.hpp"


HumanTracker::HumanTracker(std::vector<float> cameraIntrinsicsParams, int detectionInterval, 
                int cameraID, float heightOfPerson, std::string model_config, 
                std::string model_weight, std::string classFilePath) : camera(cameraID, cameraIntrinsicsParams) { 
        detectionInterval = detectionInterval; 
        heightOfPerson = heightOfPerson;
        detector.load_model(model_config, model_weight, classFilePath);
}

float HumanTracker::computeDistance(const cv::Rect& bbox) {
    float distanceInFeet = 0.0;
    distanceInFeet = (camera.fy * heightOfPerson) / bbox.height; // verify math
    return distanceInFeet;
}

std::vector<utils::bbox> HumanTracker::detectHuman(const cv::Mat& frame) {
    std::vector<utils::bbox> bboxs;
    bboxs = detector.detect(frame);
    return bboxs;
}

Obstacle HumanTracker::createObstacle(float d, cv::Rect bbox){
    cv::Mat pose = cv::Mat::eye(4, 4, CV_32F);  
    float params[]={bbox.x, bbox.y, 1};
    cv::Mat leftTopCorner(3,1,CV_32F,params);
    leftTopCorner = d * camera.Kinv * leftTopCorner;
    float width = d * bbox.width / camera.fx; // verify math
    float height = d * bbox.height / camera.fy; // verify math
    float breadth = width;
    pose.at<float>(0,3) = leftTopCorner.at<float>(0,0);
    pose.at<float>(1,3) = leftTopCorner.at<float>(1,0);
    pose.at<float>(2,3) = leftTopCorner.at<float>(2,0)-breadth/2;
    Obstacle newObstacle(pose, width, height, breadth);

    return newObstacle;
}





