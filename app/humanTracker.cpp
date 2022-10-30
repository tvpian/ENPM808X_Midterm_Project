/* Copyright 2022
 * Author(s)
 * Tharun V. Puthanveettil, Pavan Mantripragada, Yashveer Jain
 */
#include "humanTracker.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <opencv2/core/ocl.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>
#include <sstream>
#include <string>
#include <variant>
#include <vector>

#include "camera.hpp"
#include "detector.hpp"
#include "obstacle.hpp"
#include "tracker.hpp"
#include "utils.hpp"

HumanTracker::HumanTracker(const std::vector<float>& cameraIntrinsicsParams,
                           cv::Mat_<float> extrinsicMatrix, int cameraID,
                           int detectionInterval, float heightOfPerson,
                           std::string modelConfig, std::string modelWeight,
                           std::string classFilePath)
    : camera(cameraIntrinsicsParams, extrinsicMatrix, cameraID) {
  this->detectionInterval = detectionInterval;
  this->heightOfPerson = heightOfPerson;
  detector.loadModel(modelConfig, modelWeight, classFilePath);
}

HumanTracker::HumanTracker(const std::vector<float>& cameraIntrinsicsParams,
                           cv::Mat_<float> extrinsicMatrix,
                           const std::string& videoPath, int detectionInterval,
                           float heightOfPerson, std::string modelConfig,
                           std::string modelWeight, std::string classFilePath)
    : camera(cameraIntrinsicsParams, extrinsicMatrix, videoPath) {
  this->detectionInterval = detectionInterval;
  this->heightOfPerson = heightOfPerson;
  detector.loadModel(modelConfig, modelWeight, classFilePath);
}

float HumanTracker::computeDistance(const cv::Rect& bbox) {
  float distanceInFeet = 0.0;
  distanceInFeet = (camera.fy * heightOfPerson) / bbox.height;  // verify math
  return distanceInFeet;
}

std::vector<utils::bbox> HumanTracker::detectHuman(const cv::Mat& frame) {
  std::vector<utils::bbox> bboxs;
  bboxs = detector.detect(frame);
  return bboxs;
}

Obstacle HumanTracker::createObstacle(float d, cv::Rect_<float> bbox) {
  cv::Mat pose = cv::Mat::eye(4, 4, CV_32F);
  float params[] = {bbox.x, bbox.y, 1};
  cv::Mat leftTopCorner(3, 1, CV_32F, params);
  leftTopCorner = d * camera.Kinv * leftTopCorner;
  float width = d * bbox.width / camera.fx;    // verify math
  float height = d * bbox.height / camera.fy;  // verify math
  float breadth = width;
  pose.at<float>(0, 3) = leftTopCorner.at<float>(0, 0);
  pose.at<float>(1, 3) = leftTopCorner.at<float>(1, 0);
  pose.at<float>(2, 3) = leftTopCorner.at<float>(2, 0) - breadth / 2;
  Obstacle newObstacle(pose, width, height, breadth);
  newObstacle.transform(camera.H);
  return newObstacle;
}

cv::Mat HumanTracker::getFrame() { return camera.readFrame(); }

std::vector<Obstacle> HumanTracker::getObstacles(cv::Mat frame) {
  std::vector<utils::bbox> bboxs;

  if (frameCount % detectionInterval == 0) {
    bboxs = detectHuman(frame);
    tracker.init(frame, bboxs);
    frameCount = 1;  // To avoid reaching the int limit after +=1 every loop
  } else {
    bboxs = tracker.getTrackingOutput(frame);
  }
  frameCount += 1;
  std::vector<Obstacle> obstacles;
  for (auto bbox : bboxs) {
    float d = computeDistance(bbox.box);
    Obstacle obstacle = createObstacle(d, bbox.box);
    obstacles.push_back(obstacle);
  }
  display(frame, bboxs, obstacles);
  return obstacles;
}

void HumanTracker::display(cv::Mat frame, std::vector<utils::bbox> bboxs,
                           std::vector<Obstacle> obstacles) {
  tracker.drawPred(frame, bboxs, obstacles);
  cv::imshow("Tracker Output", frame);
}
