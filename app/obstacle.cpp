/* Copyright 2022
 * Author(s)
 * Tharun V. Puthanveettil, Pavan Mantripragada, Yashveer Jain
 */
#include "obstacle.hpp"

#include <vector>

Obstacle::Obstacle(cv::Mat_<float> H, float width, float height, float breadth)
    : pose{H}, Lx{width}, Ly{height}, Lz{breadth} {}

void Obstacle::transform(cv::Mat_<float> H) { pose = H * pose; }

std::vector<float> Obstacle::getCoordinates() {
  std::vector<float> coordinates;
  coordinates.push_back(pose.at<float>(0, 3));
  coordinates.push_back(pose.at<float>(1, 3));
  coordinates.push_back(pose.at<float>(2, 3));
  return coordinates;
}
