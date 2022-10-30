/* Copyright 2022
 * Author(s)
 * Tharun V. Puthanveettil, Pavan Mantripragada, Yashveer Jain
 */
#include "tracker.hpp"

#include <iostream>
#include <algorithm>
#include <opencv2/core/ocl.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>
#include <string>
#include <vector>

#include "utils.hpp"

void Tracker::init(cv::Mat& frame, std::vector<utils::bbox> target_bboxs) {
  cv::RNG rng(0);
  trackers.release();  // assuming that the ptrs inside the trackers object is
                       // deleting after calling the destructor.
  trackers = cv::MultiTracker::create();
  for (utils::bbox target_bbox : target_bboxs) {
    trackers->add(cv::TrackerCSRT::create(), frame,
                  cv::Rect2d(target_bbox.box));
    colors.push_back(cv::Scalar(rng.uniform(0, 255), rng.uniform(0, 255),
                                rng.uniform(0, 255)));
  }
}

std::vector<utils::bbox> Tracker::getTrackingOutput(cv::Mat& frame) {
  trackers->update(frame);
  std::vector<utils::bbox> updatedBboxs;
  std::vector<cv::Rect2d> objects_list = trackers->getObjects();
  std::for_each(objects_list.begin(),objects_list.end(),[&updatedBboxs](cv::Rect2d tracked_object){
    updatedBboxs.push_back({0, 100.0, cv::Rect(tracked_object)});
  });
  return updatedBboxs;
}

void Tracker::drawPred(cv::Mat& frame, std::vector<utils::bbox> target_bboxs,
                       std::vector<Obstacle> obstacles) {
  std::vector<float> coordinates;
  std::string label;
  for (unsigned i = 0; i < target_bboxs.size(); i++) {
    std::cout << "ID : " << target_bboxs[i].id << " Confidence : " << target_bboxs[i].confidence << std::endl;
    coordinates = obstacles[i].getCoordinates();
    cv::rectangle(frame, cv::Rect2d(target_bboxs[i].box), colors[i], 2, 1);
    label = "Obstacle " + std::to_string(i + 1) + " at (" +
            std::to_string(int(coordinates[0])) + ", " +
            std::to_string(int(coordinates[1])) + ", " +
            std::to_string(int(coordinates[2])) + ")";
    cv::putText(frame, label,
                cv::Point(target_bboxs[i].box.x, target_bboxs[i].box.y),
                cv::FONT_HERSHEY_SIMPLEX, 0.75, colors[i], 2);
  }
  
}
