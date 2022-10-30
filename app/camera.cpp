/* Copyright 2022
 * Author(s)
 * Tharun V. Puthanveettil, Pavan Mantripragada, Yashveer Jain
 */
#include "camera.hpp"

#include <iostream>
#include <vector>

#include "opencv2/opencv.hpp"

Camera::Camera(const std::vector<float>& cameraIntrinsicsParams,
               cv::Mat_<float> extrinsicMatrix, int camId)
    : fx{cameraIntrinsicsParams[0]},
      fy{cameraIntrinsicsParams[1]},
      s{cameraIntrinsicsParams[2]},
      cx{cameraIntrinsicsParams[3]},
      cy{cameraIntrinsicsParams[4]} {
  videoCapture.open(camId);
  if (!videoCapture.isOpened()) {
    std::cout << "Error opening video stream or file" << std::endl;
    throw("Camera Not Captured");
  }
  setCameraIntrinsics();
  setCameraExtrinsics(extrinsicMatrix);
}

Camera::Camera(const std::vector<float>& cameraIntrinsicsParams,
               cv::Mat_<float> extrinsicMatrix, std::string videoPath)
    : fx{cameraIntrinsicsParams[0]},
      fy{cameraIntrinsicsParams[1]},
      s{cameraIntrinsicsParams[2]},
      cx{cameraIntrinsicsParams[3]},
      cy{cameraIntrinsicsParams[4]} {
  videoCapture.open(videoPath);
  if (!videoCapture.isOpened()) {
    std::cout << "Error opening video stream or file" << std::endl;
    throw("Camera Not Captured");
  }
  setCameraIntrinsics();
  setCameraExtrinsics(extrinsicMatrix);
}

cv::Mat Camera::readFrame() {
  cv::Mat frame;
  videoCapture >> frame;
  if (frame.empty()) throw("Not able to read frame");
  return frame;
}

Camera::~Camera() { videoCapture.release(); }

void Camera::setCameraExtrinsics(cv::Mat_<float> extrinsicMatrix) {
  H = extrinsicMatrix;
}

void Camera::setCameraIntrinsics() {
  float params[] = {fx, s, cx, 0, fy, cy, 0, 0, 1};
  cv::Mat intrinsicMatrix(3, 3, CV_32F, params);
  K = intrinsicMatrix;
  Kinv = intrinsicMatrix.inv();
}
