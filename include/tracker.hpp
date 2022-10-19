#pragma once
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/core/ocl.hpp>
using namespace cv;
using namespace std;

#include<iostream>



class Tracker:
static Ptr<Tracker> tracker;
 public:
    Detector() {
        tracker = TrackerCSRT::create();
    }
    vector<float> predict(frame, vector<int> bbox) {
        bool ok = video.read(frame);
        Rect2d bbox(287, 23, 86, 320);

        rectangle(frame, bbox, Scalar(255, 0, 0), 2, 1);

        imshow("Tracking", frame);
        tracker->init(frame, bbox);
    }

    vector<float> update(frame, vector<int> bbox) {
            
    }






