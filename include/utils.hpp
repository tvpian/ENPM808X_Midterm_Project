/* Copyright 2022
 * Author(s) 
 * Tharun V. Puthanveettil, Pavan Mantripragada, Yashveer Jain
 */
#pragma once

#include <string>
#include <vector>
#include <opencv2/core/types.hpp>

namespace utils{
    struct bbox {
        int id;
        float confidence;
        cv::Rect box;
    };
}
