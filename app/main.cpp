#include <iostream>
#include <camera.hpp>


int main()
{
    Camera c(0);
    while(true) {
        cv::Mat frame = c.read_frame(true);
        cv::Size shape = frame.size();
        std::cout << shape.height << shape.width;

    }
    return 0;
    
}
