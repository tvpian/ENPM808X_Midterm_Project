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


cv::Mat Cam2Rob_transformation_mat = cv::Mat::eye(4,4,CV_32F);
// Cam2Rob_transformation_mat.at<float>(2,3) = 0.5;

std::vector<float> camera_intrinsic_param = {320,320,1,1,1,1};


TEST(camera_test, load_live_camera) {
  cv::Mat frame;
  try {
    Camera c(camera_intrinsic_param, Cam2Rob_transformation_mat, 0);
    frame = c.read_frame();
    SUCCEED();
    }
  catch(...) {
    FAIL() << "Failed to read frames from actual camera";
  }
}

TEST(camera_test, load_video_file) {
  cv::Mat frame;
  try {

    Camera c(camera_intrinsic_param, Cam2Rob_transformation_mat, "../data/myvideo.mp4");
    frame = c.read_frame();
    SUCCEED();
    }
  catch(...) {
    FAIL() << "Failed to read frames from video file";
  }
}

TEST(camera_test, frame_size_check1) {
  cv::Mat frame;
  try {

    Camera c(camera_intrinsic_param, Cam2Rob_transformation_mat, 0);
    frame = c.read_frame();
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

    Camera c(camera_intrinsic_param, Cam2Rob_transformation_mat, "../data/myvideo.mp4");
    frame = c.read_frame();
    }
  catch(...) {
    FAIL() << "Failed to read frames";
  }
  cv::Size shape = frame.size();
  EXPECT_GT(shape.height, 0.0);
  EXPECT_GT(shape.width, 0.0);
}

