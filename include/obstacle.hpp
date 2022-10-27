/* Copyright 2022
 * Author(s) 
 * Tharun V. Puthanveettil, Pavan Mantripragada, Yashveer Jain
 */
#pragma once

#include <opencv2/core/types.hpp>
#include <opencv2/core/mat.hpp>

class Obstacle {
    public:
        cv::Mat_<float> pose;
        float Lx;
        float Ly;
        float Lz;

        Obstacle(cv::Mat_<float> H, float width, float height, float breadth);
        ~Obstacle(){}
        void transform(cv::Mat_<float> H);
};