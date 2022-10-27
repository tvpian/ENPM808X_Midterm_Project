// Copyright [2022] <Tharun V. Puthanveettil, Pavan Mantripragada, Yashveer Jain>

#include <gtest/gtest.h>
#include <variant>
#include <vector>
#include "opencv2/opencv.hpp"
#include "opencv2/dnn.hpp"
#include "opencv2/imgproc.hpp"
#include "camera.hpp"
#include "detector.hpp"


cv::Mat Cam2Rob_transformation_mat = cv::Mat::eye(4,4,CV_32F);
// Cam2Rob_transformation_mat.at<float>(2,3) = 0.5;

std::vector<float> camera_intrinsic_param = {320,320,1,1,1,1};

TEST(dummy, should_pass) {
  EXPECT_EQ(1, 1);
}

TEST(human_tracker, camera_test_1) {
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


TEST(human_tracker, detector_test_1) {
  Detector detector;
  int test_human_count = 2;
  cv::Mat frame;
  std::string model_Config = "../model/yolov3.config";
  std::string model_Weights = "..model/yolov3.pt";
  try {
      detector.load_model(model_Config, model_Weights);
  }
  catch(...) {
    FAIL() << "Failed to load model";
  }
  try {
      frame = cv::imread("../data/test.png");
  }
  catch(...) {
    FAIL() << "Failed to read frames";
  }

  // std::vector<std::variant<int, float, cv::Rect>>
  // bboxes = detector.detect(frame);
  // std::vector<cv::Rect> bboxes = detector.detect(frame);
  // EXPECT_EQ(bboxes.size(), x);
  // EXPECT_TRUE(static_cast<int>(bboxes.size()) == x)
}
