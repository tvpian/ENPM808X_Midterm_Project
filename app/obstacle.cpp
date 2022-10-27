/* Copyright 2022
 * Author(s) 
 * Tharun V. Puthanveettil, Pavan Mantripragada, Yashveer Jain
 */
#include "obstacle.hpp"

Obstacle::Obstacle(cv::Mat_<float> H, float width, float height, float breadth)
    : pose{H}, Lx{width}, Ly{height}, Lz{breadth}{}

void Obstacle::transform(cv::Mat_<float> H){
    pose = H * pose;
}