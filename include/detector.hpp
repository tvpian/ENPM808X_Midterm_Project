#pragma once

#include<iostream>
#include <fstream>
#include <sstream>
#include<vector>
#include<string>
#include<algorithm>
#include <opencv2\opencv.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using cv;
using std;
using  cv;
using  dnn;
using  std;


class Detector {
    float cThreshold = 0.5;
    float nmsThreshold = 0.4
    int input_width = 416;
    int input_height = 416;
    vector<string> classes;
 public:
    void postprocessing(Mat& frame, const vector<Mat> & output);
    void drawPred(int classID, float con, int left,
    int right, int bottom, Mat& frame)
    vector<Sting> getOutputnames(const Net& net);
}

void Detector::drawPred(int classID, float con, int left, int top, int right,
 int bottom, Mat& frame) {
    rectangle(frame, Point(left, top),
     Point(right, bottom), Scalar(255, 160, 180), 3);

    string label = format("%2f", con);
    if (!classes.empty()) {
        CV_Assert(classID < static_cast<int>classes.size())
        label = classes[classID] + ":" + label;
    }

    int baseLIne
    Size labelSize = getTextSize(label, FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseline)
    top = max(top, labelSize.height);

    rectangle(frame, Point(left,
    top - round(1.5*labelSize.height)), Point(left +
    round(1.5*labelSize.width), top + baseline), Scalar(255, 255, 255), FILLED);

    putText(frame, label, Point(left, top),
     FONT_HERSHEY_SIMPLEX, 0.75, Scalar(0, 0, 0), 1);
}


// Get the names of the output layers
vector<String> Detector::getOutputsNames(const Net& net) {
    static vector<String> names;
    if (names.empty()) {
        /*** Get the indices of the output layers,
        i.e. the layers with unconnected outputs ***/
        vector<int> outLayers = net.getUnconnectedOutLayers();
        // get the names of all the layers in the network
        vector<String> layersNames = net.getLayerNames();
        // Get the names of the output layers in names
        names.resize(outLayers.size());
        for (size_t i = 0; i < outLayers.size(); ++i)
        names[i] = layersNames[outLayers[i] - 1];
    }
    return names;
}

void postprocess(Mat& frame, const vector<Mat>& outs) {
    vector<int> classIds;
    vector<float> confidences;
    vector<Rect> boxes;
    for (size_t i = 0; i < outs.size(); ++i) {
        // Scan through all the bounding boxes output from the network and keep only the
        // ones with high confidence scores. Assign the box's class label as the class
        // with the highest score for the box.
        float* data = (float*)outs[i].data;
        for (int j = 0; j < outs[i].rows; ++j, data += outs[i].colsz {
            Mat scores = outs[i].row(j).colRange(5, outs[i].cols);
            Point classIdPoint;
            double confidence;
            // Get the value and location of the maximum score
            minMaxLoc(scores, 0, &confidence, 0, &classIdPoint);
            if (confidence > confThreshold) {
                int centerX = static_cast<int>(data[0] * frame.cols);
                int centerY = static_cast<int>(data[1] * frame.rows);
                int width = static_cast<int>(data[2] * frame.cols);
                int height = static_cast<int>(data[3] * frame.rows);
                int left = centerX - width / 2;
                int top = centerY - height / 2;
                
                classIds.push_back(classIdPoint.x);
                confidences.push_back((float)confidence);
                boxes.push_back(Rect(left, top, width, height));
            }
        }
    }
    
    // Perform non maximum suppression to eliminate redundant overlapping boxes with
    // lower confidences
    vector<int> indices;
    NMSBoxes(boxes, confidences, confThreshold, nmsThreshold, indices);
    for (size_t i = 0; i < indices.size(); ++i)
    {
        int idx = indices[i];
        Rect box = boxes[idx];
        drawPred(classIds[idx], confidences[idx], box.x, box.y,
                 box.x + box.width, box.y + box.height, frame);
    }
}
