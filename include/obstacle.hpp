/* Copyright 2022
 * Author(s)
 * Tharun V. Puthanveettil, Pavan Mantripragada, Yashveer Jain
 */
#pragma once

#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>
#include <vector>

/**
 * @brief A class to store obstacle
 * data and transform obstacles from
 * one frame to another.
 */
class Obstacle {
 public:
  /** @brief pose of the obstacle in the current frame */
  cv::Mat_<float> pose;
  /** @brief width of the obstacle */
  float Lx;
  /** @brief height of the obstacle */
  float Ly;
  /** @brief breadth of the obstacle */
  float Lz;

  /**
   * @brief Constructor
   *
   * @param H pose of the obstacle
   * @param width width of the obstacle
   * @param height height of the obstacle
   * @param breadth breadth of the obstacle
   */
  Obstacle(cv::Mat_<float> H, float width, float height, float breadth);

  /**
   * @brief Destructor
   */
  ~Obstacle() {}

  /**
   * @brief Transforms the object from current frame
   *        new frame given by H
   *
   * @param H 4x4 transformation
   */
  void transform(cv::Mat_<float> H);

  /**
   * @brief outputs the coordinates of obstacle origin
   *
   * @return origin of obstacle in the current reference frame
   */
  std::vector<float> getCoordinates();
};
