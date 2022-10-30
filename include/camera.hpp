/* Copyright 2022
 * Author(s)
 * Tharun V. Puthanveettil, Pavan Mantripragada, Yashveer Jain
 */
#pragma once
#include <iostream>
#include <vector>

#include "opencv2/opencv.hpp"

/**
 * @brief Camera class
 * @details Handles the camera stream
 */
class Camera {
 private:
  /** @brief video capture object to capture frames */
  cv::VideoCapture videoCapture;

 public:
  /** @brief focal length in x direction */
  float fx;
  /** @brief focal length in y direction */
  float fy;
  /** @brief sensor skewness */
  float s;
  /** @brief x location of optical center */
  float cx;
  /** @brief y location of optical center */
  float cy;
  /** @brief composed intrinsic matrix of camera */
  cv::Mat_<float> K;
  /** @brief inverse of intrinsic matrix */
  cv::Mat_<float> Kinv;
  /** @brief camera extrinsics parameters */
  cv::Mat_<float> H;

  /**
   * @brief Constructor
   * @param cameraIntrinsicsParams Five intrinsic parameters of camera
   * @param extrinsicMatrix 4x4 extrinsic matrix of camera w.r.t robot frame
   * @param camId device id for opening camera
   */
  Camera(const std::vector<float>& cameraIntrinsicsParams,
         cv::Mat_<float> extrinsicMatrix, int camId = 0);

  /**
   * @brief Constructor Overloader
   * @param cameraIntrinsicsParams Five intrinsic parameters of camera
   * @param extrinsicMatrix 4x4 extrinsic matrix of camera w.r.t robot frame
   * @param videoPath to stream video from a file
   */
  Camera(const std::vector<float>& cameraIntrinsicsParams,
         cv::Mat_<float> extrinsicMatrix, std::string videoPath);

  /**
   * @brief read a frame
   * @return the frame which is read
   */
  cv::Mat readFrame();

  /**
   * @brief Destroy the camera object
   * @details release the video capture stream
   */
  ~Camera();

  /**
   * @brief Sets extrinsic matrix
   * @param extrinsicMatrix 4x4 camera extrinsic matrix
   */
  void setCameraExtrinsics(cv::Mat_<float> extrinsicMatrix);

  /**
   * @brief Sets intrinsic matrix
   */
  void setCameraIntrinsics();
};
