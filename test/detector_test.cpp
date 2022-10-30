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

TEST(detector_test, load_model) {
  Detector detector;
  std::string model_Config = "../model_utils/yolov3.cfg";
  std::string model_Weights = "../model_utils/yolov3.weights";
  try {
      detector.load_model(model_Config, model_Weights);
      SUCCEED();
  }
  catch(...) {
    FAIL() << "Failed to load model";
  }
}

TEST(detector_test, output_classes_count) {
  Detector detector;
  std::string model_Config = "../model_utils/yolov3.cfg";
  std::string model_Weights = "../model_utils/yolov3.weights";
  std::vector<std::string>::size_type expectedCount = 3; 
  try {
      detector.load_model(model_Config, model_Weights);
      std::vector<std::string> outputs = detector.getOutputNames();
      EXPECT_EQ(expectedCount, outputs.size());
  }
  catch(...) {
    FAIL() << "Failed to load model";
  }
}

TEST(detector_test, blob_size) {
  Detector detector;
  cv::Mat frame;
  std::string testImage = "../data/test_human.jpg";
  try {
    frame = cv::imread(testImage);
    cv::Mat blob = detector.preprocessing(frame);
    EXPECT_EQ(4, blob.dims);
  }
  catch(...) {
    FAIL() << "Failed to read image";
  }
}

TEST(detector_test, detection_count) {
  Detector detector;
  cv::Mat frame;
  std::string model_Config = "../model_utils/yolov3.cfg";
  std::string model_Weights = "../model_utils/yolov3.weights";
  std::string testImage = "../data/test_humans.jpg";
  std::vector<utils::bbox>::size_type expectedCount = 3;

  try {
      detector.load_model(model_Config, model_Weights);
  }
  catch(...) {
    FAIL() << "Failed to load model";
  }
  try {
      frame = cv::imread(testImage);
  }
  catch(...) {
    FAIL() << "Failed to read image";
  }
  std::vector<utils::bbox> bboxes = detector.detect(frame);
  
  EXPECT_EQ(expectedCount, bboxes.size());
}

TEST(detector_test, detection_accuracy) {
  Detector detector;
  cv::Mat frame;
  std::string model_Config = "../model_utils/yolov3.cfg";
  std::string model_Weights = "../model_utils/yolov3.weights";
  std::string testImage = "../data/test_human.jpg";
  std::vector<utils::bbox>::size_type expectedCount = 1;
  float gtX = 110;
  float gtY = 70;
  float gtWidth = 130;
  float gtHeight = 425;
  try {
      detector.load_model(model_Config, model_Weights);
  }
  catch(...) {
    FAIL() << "Failed to load model";
  }
  try {
      frame = cv::imread(testImage);
  }
  catch(...) {
    FAIL() << "Failed to read";
  }
  float maxPixelDistance = 0.1 * float(std::min(frame.rows,frame.cols));
  float maxWidthDeviation = 0.1 * float(frame.cols);
  float maxHeightDeviation = 0.1 * float(frame.rows); 
  std::vector<utils::bbox> bboxes = detector.detect(frame);
  EXPECT_EQ(expectedCount, bboxes.size());
  float PixelDistance = std::abs(bboxes[0].box.x - gtX) + std::abs(bboxes[0].box.y - gtY);
  float WidthDeviation = std::abs(bboxes[0].box.width - gtWidth);
  float HeightDeviation = std::abs(bboxes[0].box.height - gtHeight);
  EXPECT_GT(maxPixelDistance, PixelDistance);
  EXPECT_GT(maxWidthDeviation, WidthDeviation);
  EXPECT_GT(maxHeightDeviation, HeightDeviation);
}