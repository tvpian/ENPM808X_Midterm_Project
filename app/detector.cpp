/* Copyright 2022
 * Author(s)
 * Tharun V. Puthanveettil, Pavan Mantripragada, Yashveer Jain
 */
#include "detector.hpp"

#include <fstream>
#include <iostream>
#include <opencv2/dnn.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <sstream>

#include "utils.hpp"

void Detector::loadModel(std::string modelConfig, std::string modelWeights,
                         std::string classFilePath, const std::string& device) {
  net = cv::dnn::readNetFromDarknet(modelConfig, modelWeights);
  if (device == "cpu") {
    std::cout << "Using CPU device" << std::endl;
    net.setPreferableBackend(cv::dnn::DNN_TARGET_CPU);
  } else if (device == "gpu") {
    std::cout << "Using GPU device" << std::endl;
    net.setPreferableBackend(cv::dnn::DNN_BACKEND_CUDA);
    net.setPreferableTarget(cv::dnn::DNN_TARGET_CUDA);
  }

  // Load names of classes
  std::ifstream ifs(classFilePath.c_str());
  std::string line;
  while (std::getline(ifs, line)) classes.push_back(line);
}

std::vector<std::string> Detector::getOutputNames() {
  static std::vector<std::string> names;
  if (names.empty()) {
    // Get the indices of the output layers, i.e. the layers with unconnected
    // outputs
    std::vector<int> outLayers = net.getUnconnectedOutLayers();

    // get the names of all the layers in the network
    std::vector<std::string> layersNames = net.getLayerNames();

    // Get the names of the output layers in names
    names.resize(outLayers.size());
    for (size_t i = 0; i < outLayers.size(); ++i)
      names[i] = layersNames[outLayers[i] - 1];
  }
  return names;
}

cv::Mat Detector::preProcessing(cv::Mat& frame) {
  cv::Mat blob;
  cv::dnn::blobFromImage(frame, blob, 1 / 255.0,
                         cv::Size(inputWidth, inputHeight), cv::Scalar(0, 0, 0),
                         true, false);
  return blob;
}

std::vector<utils::bbox> Detector::detect(cv::Mat frame) {
  std::vector<cv::Mat> outs;
  std::vector<utils::bbox> bbox;
  cv::Mat blob = preProcessing(frame);
  net.setInput(blob);
  net.forward(outs, getOutputNames());
  std::vector<utils::bbox> bboxes = postProcessing(frame, outs);

  return bboxes;
}

std::vector<utils::bbox> Detector::postProcessing(
    const cv::Mat& frame, const std::vector<cv::Mat>& outs) {
  std::vector<int> classIds;
  std::vector<float> confidences;
  std::vector<cv::Rect> boxes;
  std::vector<utils::bbox> bboxes;
  utils::bbox bbox;

  for (size_t i = 0; i < outs.size(); ++i) {
    float* data = (float*)outs[i].data;
    for (int j = 0; j < outs[i].rows; ++j, data += outs[i].cols) {
      cv::Mat scores = outs[i].row(j).colRange(5, outs[i].cols);
      cv::Point classIdPoint;
      double confidence;
      cv::minMaxLoc(scores, 0, &confidence, 0, &classIdPoint);
      if (confidence > cThreshold) {
        int centerX = (int)(data[0] * frame.cols);
        int centerY = (int)(data[1] * frame.rows);
        int width = (int)(data[2] * frame.cols);
        int height = (int)(data[3] * frame.rows);
        int left = centerX - width / 2;
        int top = centerY - height / 2;

        classIds.push_back(classIdPoint.x);
        confidences.push_back((float)confidence);
        boxes.push_back(cv::Rect(left, top, width, height));
      }
    }
  }
  std::vector<int> indices;
  cv::dnn::NMSBoxes(boxes, confidences, cThreshold, nmsThreshold, indices);
  for (size_t i = 0; i < indices.size(); ++i) {
    int idx = indices[i];
    cv::Rect box = boxes[idx];
    bbox.id = classIds[idx];
    if (bbox.id != 0) {
      continue;
    }
    bbox.box = box;
    bbox.confidence = confidences[idx];
    bboxes.push_back(bbox);
  }
  return bboxes;
}
