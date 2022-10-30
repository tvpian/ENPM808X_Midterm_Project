// Copyright [2022] <Tharun V. Puthanveettil, Pavan Mantripragada, Yashveer Jain>

#include <gtest/gtest.h>
#include <vector>
#include <cmath>
#include <algorithm>
#include "opencv2/opencv.hpp"
#include "opencv2/dnn.hpp"
#include "opencv2/imgproc.hpp"
#include "utils.hpp"
#include "camera.hpp"
#include "detector.hpp"


cv::Mat Cam2RobTransformationMat = cv::Mat::eye(4,4,CV_32F);
std::vector<float> cameraIntrinsicParam = {320,320,1,1,1,1};

TEST(camera_test, load_live_camera) {
  cv::Mat frame;
  try {
    Camera c(cameraIntrinsicParam, Cam2RobTransformationMat, 0);
    frame = c.readFrame();
    SUCCEED();
    }
  catch(...) {
    FAIL() << "Failed to read frames from actual camera";
  }
}

TEST(camera_test, load_video_file) {
  cv::Mat frame;
  try {

    Camera c(cameraIntrinsicParam, Cam2RobTransformationMat, "../data/myvideo.mp4");
    frame = c.readFrame();
    SUCCEED();
    }
  catch(...) {
    FAIL() << "Failed to read frames from video file";
  }
}

TEST(camera_test, frame_size_check1) {
  cv::Mat frame;
  try {

    Camera c(cameraIntrinsicParam, Cam2RobTransformationMat, 0);
    frame = c.readFrame();
    }
  catch(...) {
    FAIL() << "Failed to read frames";
  }
  cv::Size shape = frame.size();
  EXPECT_GT(shape.height, 0.0);
  EXPECT_GT(shape.width, 0.0);
}

TEST(camera_test, frame_size_check2) {
  cv::Mat frame;
  try {

    Camera c(cameraIntrinsicParam, Cam2RobTransformationMat, "../data/myvideo.mp4");
    frame = c.readFrame();
    }
  catch(...) {
    FAIL() << "Failed to read frames";
  }
  cv::Size shape = frame.size();
  EXPECT_GT(shape.height, 0.0);
  EXPECT_GT(shape.width, 0.0);
}

