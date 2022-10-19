/* Copyright 2022
 * Author(s) 
 * Tharun V. Puthanveettil, Pavan Mantripragada, Yashveer Jain
 */
#pragma once

#include<iostream>
#include <fstream>
#include <sstream>
#include<vector>
#include<string>
#include<algorithm>
#include <variant>
#include <opencv2\opencv.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

class Detector {
 private: 
    float cThreshold = 0.5;
    float nmsThreshold = 0.4
    int input_width = 416;
    int input_height = 416;
    std::vector<string> classes;
    dnn::Net net;

 public:
    /**
     * @brief Construct a new Detector object
     * 
     * @param a 
     * @param b 
     * @param c 
     * @param d 
     */
    Detector(float a, float b, int c, int d) 
    :cThreshold{a},nmsThreshold{b},input_width{c},input_height{d} {}
    /**
     * @brief Destroy the Detector object
     * 
     */
    ~Detector(){}

    /**
     * @brief Load the model configuaration
     * 
     * @param model_Config  DNN model configuaration 
     * @param model_Weights DNN model trained weights
     */
    void load_model(string model_Config, string model_Weights);

    /**
     * @brief Detect and extract bounding boxes of detected targets
     * 
     * @param frame The image in which humans must be detected
     * @return a list of class id, detection confidence, bounding box
     */
    std::vector<std::variant<int,float,cv::Rect>> detect(cv::Mat frame);

    /**
     * @brief Apply NMS for optimization and visualization
     * 
     * @param frame Input image to postprocess
     * @param outs Names of the output layers
     * @return a list of class id, detection confidence, bounding box 
     */
    std::vector<std::variant<int,float,cv::Rect>> postprocess(Mat& frame, const vector<Mat>& outs);

    /**
     * @brief Draw bounding box for the frame.
     * 
     * @param classId Class id in the Coco dataset
     * @param conf Confidence score 
     * @param left Left most cordinate of the bounding box
     * @param top Top most coordinate of the bounding box
     * @param right RIght most coordinate of the bounding box
     * @param bottom Bottom most coordinate of the bounding box
     * @param frame Input image frame
     */
    void drawPred(int classId, float conf, int left, int top, int right, int bottom, Mat& frame);    
    std::vector<String> getOutputnames(const Net& net);
}