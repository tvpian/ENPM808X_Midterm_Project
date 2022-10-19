#pragma once

#include<iostream>
#include <opencv2\opencv.hpp>


using cv;

using std;


class Camera {
    Mat frame;
    double<vector> cameraCoord;
    videoCapture cap;

 public:
    Camera() {
      if (!cap.isOpened()) {
        cout << "Error in opening the camera" << endl
        return -1;
      }
    }
    Mat read_frame() {
      cap >> frame;
      if (frame.empty())
        break;
      imshow("Frame", frame);
      return frame;
    }
    ~Camera() {
      cap.release();
      destroyAllWindows();
    }
}
