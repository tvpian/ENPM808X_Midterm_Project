/* Copyright 2022
 * Author(s)
 * Tharun V. Puthanveettil, Pavan Mantripragada, Yashveer Jain
 */
#pragma once
#include <iostream>
#include <opencv2/core/ocl.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>
#include <string>
#include <vector>

#include "obstacle.hpp"
#include "utils.hpp"

/**
 * @brief Tracker classs
 */
class Tracker {
 private:
  /** @brief Pointer to the multi-tracker object */
  cv::Ptr<cv::MultiTracker> trackers;
  /** @brief list of colors for bounding boxes */
  std::vector<cv::Scalar> colors;

 public:
  /**
   * @brief Constructor of Tracker class
   */
  Tracker() {}

  /**
   * @brief Destructor of Tracker class
   */
  ~Tracker() {}

  /**
   * @brief Initialize the tracker on the initial frame
   *
   * @param frame input frame
   * @param target_bboxs initial bounding boxs
   */
  void init(cv::Mat& frame, std::vector<utils::bbox> target_bboxs);

  /**
   * @brief Extract the bounding box of tracker target in next frame
   *
   * @param frame Input image frame
   * @return updated bounding boxes
   */
  std::vector<utils::bbox> getTrackingOutput(cv::Mat& frame);

  /**
   * @brief Draw bounding box for the tracked target
   *
   * @param frame Input image frame
   * @param bbox Detected bounding box coordinate from previous frame
   * @param obstacles detected obstacles
   */
  void drawPred(cv::Mat& frame, std::vector<utils::bbox> target_bboxs,
                std::vector<Obstacle> obstacles);
};
