/* Copyright 2022
 * Author(s)
 * Tharun V. Puthanveettil, Pavan Mantripragada, Yashveer Jain
 */
#pragma once

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

/**
 * @brief Wrapper class for
 * Human detection and tracking
 */
class HumanTracker {
 private:
  /** @brief no. of humans tracked at current frame */
  int CurrentHumanCounts = 0;
  /** @brief no. of humans detected so far */
  int humansDetectedSoFar = 0;
  /** @brief no. of frames elapsed until now */
  int frameCount = 0;
  /** @brief no. of frames after which detection is called again*/
  int detectionInterval;
  /** @brief world height (in ft.) of a person assumed */
  int heightOfPerson;
  /** @brief detector object */
  Detector detector;
  /** @brief camera object */
  Camera camera;
  /** @brief tracker object */
  Tracker tracker;

 public:
  /**
   * @brief Constructor
   *
   * @param cameraIntrinsicsParams 5 camera intrinsic params
   * @param extrinsicMatrix 4x4 extrinsic matrix of camera w.r.t robot frame
   * @param cameraID device id
   * @param detectionInterval no. of frames after which detection is called
   * again
   * @param heightOfPerson world height (in ft.) of a person assumed
   * @param modelConfig model configuration file path
   * @param modelWeight model weights file path
   * @param classFilePath coco dataset class names files path
   */
  HumanTracker(const std::vector<float>& cameraIntrinsicsParams,
               cv::Mat_<float> extrinsicMatrix, int cameraID = 0,
               int detectionInterval = 50, float heightOfPerson = 6,
               std::string modelConfig = "../model_utils/yolov3.cfg",
               std::string modelWeight = "../model_utils/yolov3.weights",
               std::string classFilePath = "../model_utils/coco.names");

  /**
   * @brief Constructor Overloader
   *
   * @param cameraIntrinsicsParams 5 camera intrinsic params
   * @param extrinsicMatrix 4x4 extrinsic matrix of camera w.r.t robot frame
   * @param videoPath video file path
   * @param detectionInterval no. of frames after which detection is called
   * again
   * @param heightOfPerson world height (in ft.) of a person assumed
   * @param modelConfig model configuration file path
   * @param modelWeight model weights file path
   * @param classFilePath coco dataset class names files path
   */
  HumanTracker(const std::vector<float>& cameraIntrinsicsParams,
               cv::Mat_<float> extrinsicMatrix, const std::string& videoPath,
               int detectionInterval = 50, float heightOfPerson = 6,
               std::string modelConfig = "../model_utils/yolov3.cfg",
               std::string modelWeight = "../model_utils/yolov3.weights",
               std::string classFilePath = "../model_utils/coco.names");

  /**
   * @brief Method to estimate distance of each human
   *
   * @param bbox bounding box whose distance needs to be computed
   * @return distance of bounding box
   */
  float computeDistance(const cv::Rect& bbox);

  /**
   * @brief detection wrapper method for human tracker class
   *
   * @param frame frame in which obstacles need to be detected
   * @return list of bounding boxes of all detected humans
   */
  std::vector<utils::bbox> detectHuman(const cv::Mat& frame);

  /**
   * @brief get frame wrapper method for human tracker class
   */
  cv::Mat getFrame();

  /**
   * @brief Created obstacles from bounding box and depth
   *
   * @param d distance of detected obstacle
   * @param bbox bounding box of the obstacle
   * @return obstacle object
   */
  Obstacle createObstacle(float d, cv::Rect_<float> bbox);

  /**
   * @brief Detects and trackes obstacles in a frame
   *
   * @param frame current frame
   * @return list of all obstacles
   */
  std::vector<Obstacle> getObstacles(cv::Mat frame);

  /**
   * @brief Display method to draw bounding boxes on image
   *
   * @param frame current frame
   * @param bboxs bounding boxes of the obstacles
   * @param obstacles list of all obstacles
   */
  void display(cv::Mat frame, std::vector<utils::bbox> bboxs,
               std::vector<Obstacle> obstacles);
};
