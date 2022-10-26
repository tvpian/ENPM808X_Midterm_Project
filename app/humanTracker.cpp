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


class HumanTracker{
 private:
    int CurrentHumanCounts = 0;
    int humansDetectedSoFar = 0;
    Detector detector();
    Camera camera();
    Tracker tracker();

 public:
    float computeDistance(const cv::Rect& bbox);
    std::vector<utils::bbox> detectHuman(const cv::Mat& frame);
    cv::Mat getImage();
    std::vector<utils::bbox> trackHuman(std::vector<utils::bbox>& bboxs);
};

float computeDistance(const cv::Rect& bbox) {
    float distance = 0.0;
    float focalLength = 0.0;
    float distanceInFeet = 0.0;
    float heightOfPerson = 0.0;
    distanceInFeet = (focalLength * heightOfPerson) / bbox.height;
    return distanceInFeet;
}