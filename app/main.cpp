/* Copyright 2022
 * Author(s) 
 * Tharun V. Puthanveettil, Pavan Mantripragada, Yashveer Jain
 */

#include <iostream>
#include "camera.hpp"
#include <detector.hpp>
#include <tracker.hpp>


int main() {
    Camera c(0);
    while (true) {
        cv::Mat frame = c.read_frame();
        cv::Size shape = frame.size();
        std::cout << shape.height << shape.width;
    }
    return 0;
}
