/* Copyright 2022
 * Author(s)
 * Tharun V. Puthanveettil, Pavan Mantripragada, Yashveer Jain
 */
#pragma once

#include <opencv2/core/types.hpp>
#include <string>
#include <vector>

namespace utils {
struct bbox {
  int id;
  float confidence;
  cv::Rect box;
};
}  // namespace utils
