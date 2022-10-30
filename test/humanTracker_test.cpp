// Copyright [2022] <Tharun V. Puthanveettil, Pavan Mantripragada, Yashveer Jain>

#include <gtest/gtest.h>
#include <variant>
#include <vector>
#include <cmath>
#include "opencv2/opencv.hpp"
#include "opencv2/dnn.hpp"
#include "opencv2/imgproc.hpp"
#include "camera.hpp"
#include "detector.hpp"
#include "tracker.hpp"
#include "utils.hpp"
#include "humanTracker.hpp"


TEST(humanTracker_test, compute_distance) {
  float fy = 1.0;
  std::vector<float> cameraIntrinsicsParams = {320, fy, 1, 1, 1, 1};
  cv::Mat_<float> extrinsicMatrix = cv::Mat::eye(4, 4, CV_32F);
  std::string model_config = "../model_utils/yolov3.cfg";
  std::string classFilePath = "../model_utils/coco.names";
  std::string model_weight = "../model_utils/yolov3.weights";
  HumanTracker humantracker(cameraIntrinsicsParams, extrinsicMatrix,
                "../data/myvideo.mp4", 10, 6, 
                model_config, model_weight, classFilePath);
  std::vector<utils::bbox> bboxs = humantracker.detectHuman(humantracker.getFrame());
  float actualDistance = 6 * (fy/bboxs[0].box.height);
  float computedDistance = humantracker.computeDistance(bboxs[0].box);
  EXPECT_NEAR(computedDistance, actualDistance, 1e-5);
} 

TEST(humanTracker_test, create_obstacle) {
  std::string model_config = "../model_utils/yolov3.cfg";
  std::string classFilePath = "../model_utils/coco.names";
  std::string model_weight = "../model_utils/yolov3.weights";
  cv::Rect myRect(0.0, 0.0, 30.0, 20.0);
  float data[16] = { 0, 0, -1, 0, 1, 0, 0, 0.5, 0, -1, 0, 0.5, 0, 0, 0, 1 };
  cv::Mat extrinsicMatrix = cv::Mat(4, 4, CV_32F, data); 
  std::vector<float> cameraIntrinsicsParams = {50, 50, 0, 0, 0};
  float actualDistance =  5;
  HumanTracker humantracker(cameraIntrinsicsParams, extrinsicMatrix,
                "../data/myvideo.mp4", 10, 6, 
                model_config, model_weight, classFilePath);
  Obstacle obstacle = humantracker.createObstacle(actualDistance, myRect);
  EXPECT_FLOAT_EQ(3.0, obstacle.Lx);
  EXPECT_FLOAT_EQ(2.0, obstacle.Ly);
  EXPECT_FLOAT_EQ(3.0, obstacle.Lz);
  EXPECT_FLOAT_EQ(-3.5, obstacle.pose.at<float>(0, 3));
  EXPECT_FLOAT_EQ(0.5, obstacle.pose.at<float>(1, 3));
  EXPECT_FLOAT_EQ(0.5, obstacle.pose.at<float>(2, 3));
} 

TEST(humanTracker_test, get_obstacle) {
  std::string model_config = "../model_utils/yolov3.cfg";
  std::string classFilePath = "../model_utils/coco.names";
  std::string model_weight = "../model_utils/yolov3.weights";
  std::vector<float> cameraIntrinsicsParams = {320, 320, 1, 1, 1};
  cv::Mat_<float> extrinsicMatrix = cv::Mat::eye(4, 4, CV_32F);
  std::vector<Obstacle>::size_type obstaclesNum = 36;
  HumanTracker humantracker(cameraIntrinsicsParams, extrinsicMatrix,
                "../data/myvideo.mp4", 10, 6, 
                model_config, model_weight, classFilePath);
  std::vector<Obstacle> obstacles = humantracker.getObstacles(humantracker.getFrame());
  EXPECT_EQ(obstaclesNum, obstacles.size());
}
