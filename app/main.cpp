/** Copyright [2022]
 * @Authors <Tharun V. Puthanveettil, Pavan Mantripragada, Yashveer Jain>
**/
#include <iostream>
#include "camera.hpp"
#include "detector.hpp"
#include "tracker.hpp"


int main() {
    Camera c(0);
    for (int i = 0; i<5; i++) {
        cv::Mat frame = c.read_frame();
        cv::Size shape = frame.size();
        std::cout << shape.height << shape.width << std::endl;
    }
    return 0;
}
