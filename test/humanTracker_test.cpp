/* Copyright 2022
 * Author(s)
 * Tharun V. Puthanveettil, Pavan Mantripragada, Yashveer Jain
 */
#include "humanTracker.hpp"

#include <gtest/gtest.h>

#include <cmath>
#include <variant>
#include <vector>

#include "camera.hpp"
#include "detector.hpp"
#include "opencv2/dnn.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include "tracker.hpp"
#include "utils.hpp"

TEST(humanTracker_test, compute_distance) {
  float fy = 1.0;
  std::vector<float> cameraIntrinsicsParams = {320, fy, 1, 1, 1, 1};
  cv::Mat_<float> extrinsicMatrix = cv::Mat::eye(4, 4, CV_32F);
  std::string modelConfig = "../model_utils/yolov3.cfg";
  std::string classFilePath = "../model_utils/coco.names";
  std::string modelWeight = "../model_utils/yolov3.weights";
  try {
    HumanTracker humantracker(cameraIntrinsicsParams, extrinsicMatrix,
                              "../data/myvideo.mp4", 10, 6, modelConfig,
                              modelWeight, classFilePath);
    std::vector<utils::bbox> bboxs =
        humantracker.detectHuman(humantracker.getFrame());
    float actualDistance = 6 * (fy / bboxs[0].box.height);
    float computedDistance = humantracker.computeDistance(bboxs[0].box);
    EXPECT_NEAR(computedDistance, actualDistance, 1e-5);
  } catch (...) {
    FAIL() << "Failed to read video";
  }
}

TEST(humanTracker_test, create_obstacle) {
  std::string modelConfig = "../model_utils/yolov3.cfg";
  std::string classFilePath = "../model_utils/coco.names";
  std::string modelWeight = "../model_utils/yolov3.weights";
  cv::Rect myRect(0.0, 0.0, 30.0, 20.0);
  float data[16] = {0, 0, -1, 0, 1, 0, 0, 0.5, 0, -1, 0, 0.5, 0, 0, 0, 1};
  cv::Mat extrinsicMatrix = cv::Mat(4, 4, CV_32F, data);
  std::vector<float> cameraIntrinsicsParams = {50, 50, 0, 0, 0};
  try {
    float actualDistance = 5;
    HumanTracker humantracker(cameraIntrinsicsParams, extrinsicMatrix,
                              "../data/myvideo.mp4", 10, 6, modelConfig,
                              modelWeight, classFilePath);
    Obstacle obstacle = humantracker.createObstacle(actualDistance, myRect);
    EXPECT_FLOAT_EQ(3.0, obstacle.Lx);
    EXPECT_FLOAT_EQ(2.0, obstacle.Ly);
    EXPECT_FLOAT_EQ(3.0, obstacle.Lz);
    EXPECT_FLOAT_EQ(-3.5, obstacle.pose.at<float>(0, 3));
    EXPECT_FLOAT_EQ(0.5, obstacle.pose.at<float>(1, 3));
    EXPECT_FLOAT_EQ(0.5, obstacle.pose.at<float>(2, 3));
  } catch (...) {
    FAIL() << "Failed to read video";
  }
}

TEST(humanTracker_test, get_obstacle) {
  std::string modelConfig = "../model_utils/yolov3.cfg";
  std::string classFilePath = "../model_utils/coco.names";
  std::string modelWeight = "../model_utils/yolov3.weights";
  std::vector<float> cameraIntrinsicsParams = {320, 320, 1, 1, 1};
  cv::Mat_<float> extrinsicMatrix = cv::Mat::eye(4, 4, CV_32F);
  std::vector<Obstacle>::size_type obstaclesNum = 36;
  try {
    HumanTracker humantracker(cameraIntrinsicsParams, extrinsicMatrix,
                              "../data/myvideo.mp4", 10, 6, modelConfig,
                              modelWeight, classFilePath);
    std::vector<Obstacle> obstacles =
        humantracker.getObstacles(humantracker.getFrame());
    EXPECT_EQ(obstaclesNum, obstacles.size());
  } catch (...) {
    FAIL() << "Failed to read video";
  }
}
