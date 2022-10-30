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



std::string model_Config = "../model_utils/yolov3.cfg";
std::string model_Weights = "../model_utils/yolov3.weights";
std::string classFilePath = "../model_utils/coco.names";

TEST(tracker_test, tracking_check) {
  Detector detector;
  cv::Mat frame;
  cv::VideoCapture video_cap;
  float minThreshold = 2; // distance between bbox of 2 consecutive frame
  float prob = 0.4; // condition to check whether more than 80% people are tracked.
  Tracker tracker;
  auto success = 0;
  float probSuccess = 0.0;
  int frameCount = 2;
  try {
    detector.loadModel(model_Config, model_Weights, classFilePath);
  }
  catch(...) {
    FAIL() << "Failed to load model";
  }
  try {
      video_cap.open("../data/myvideo.mp4");
      video_cap >> frame;
  }
  catch(...) {
    FAIL() << "Failed to read video";
  }

  std::vector<utils::bbox> bboxs = detector.detect(frame);
  tracker.init(frame, bboxs);
  
  std::vector<utils::bbox> trackingbboxs, detectbboxs;
  for (int count = 0; count <frameCount; count++){
    video_cap >> frame;
    trackingbboxs = tracker.getTrackingOutput(frame);
    detectbboxs = detector.detect(frame);
    for (utils::bbox tbox: trackingbboxs){
      cv::Rect tbbox = tbox.box;
      float tcx = tbbox.x+tbbox.width/2;
      float tcy = tbbox.y+tbbox.height/2;
      float min_distance = 1000;

      for (auto dbox: detectbboxs){
          cv::Rect dbbox = dbox.box;
          float dcx = dbbox.x+dbbox.width/2;
          float dcy = dbbox.y+dbbox.height/2;
          float dist = sqrt(pow((dcx-tcx),2)+pow((dcy-tcy),2));
          if (dist<min_distance){
            //std::cout<< dist <<std::endl;
            min_distance = dist;
          }
      }
      if (min_distance<minThreshold){
        success+=1;
      }
    }
    probSuccess += success/trackingbboxs.size();
  }
  probSuccess/=frameCount;
  std::cout<< "Prob Success : " << probSuccess<<std::endl;
  EXPECT_GT(probSuccess,prob);
}

