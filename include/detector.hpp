/* Copyright 2022
 * Author(s) 
 * Tharun V. Puthanveettil, Pavan Mantripragada, Yashveer Jain
 */
#pragma once

#include<iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "utils.hpp"

/**
* @brief A detector class for getting
* class ids, detectection confidence,
* and bounding boxes for obstacles.
*/
class Detector {
 private:
/** @brief confidence threshold */
  float cThreshold = 0.5;
/** @brief non-maximal suppression threshold */
  float nmsThreshold = 0.4;
/** @brief required input image width */
  int inputWidth = 416;
/** @brief required input image height */
  int inputHeight = 416;
/** @brief list of classes */
  std::vector<std::string> classes;
/** @brief model object */
  cv::dnn::Net net;

 public:
    /**
     * @brief Construct a new Detector object
     * 
     * @param a confidence threshold
     * @param b non-maximal suppression threshold
     * @param c required input image width
     * @param d required input image height
     */
    explicit Detector(float a = 0.5, float b = 0.4, int c = 416, int d = 416)
    :cThreshold{a}, nmsThreshold{b}, inputWidth{c}, inputHeight{d} {
    }
    /**
     * @brief Destroy the Detector object
     */

    /**
     * @brief Destroy the Detector object
     * 
     */
    ~Detector() {
    }

  /**
   * @brief Preprocess input frame
   * 
   * @param frame Input image frame
   */
  cv::Mat preprocessing(cv::Mat& frame);

    /**
     * @brief Load the model configuaration
     * 
     * @param model_Config  DNN model configuaration 
     * @param model_Weights DNN model trained weights
     */
    void load_model(std::string model_Config = "../model_utils/yolov3.cfg", std::string model_Weights = "../model_utils/yolov3.weights", 
                std::string classFilePath="model_utils/coco.names", std::string device = "cpu");

    /**
     * @brief Get the Outputnames object
     * 
     * @param  
     * @return std::vector<String> 
     */
    std::vector<std::string> getOutputNames();

    /**
     * @brief Detect and extract bounding boxes of detected targets
     * 
     * @param frame The image in which humans must be detected
     * @return a list of class id, detection confidence, bounding box
     */
    std::vector<utils::bbox> detect(cv::Mat frame);

    /**
     * @brief Apply NMS for optimization and visualization
     * 
     * @param frame Input image to postprocess
     * @param outs Names of the output layers
     * @return a list of class id, detection confidence, bounding box 
     */
    std::vector<utils::bbox> postprocessing(cv::Mat& frame,
     const std::vector<cv::Mat>& outs);
};
