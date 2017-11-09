#ifndef NAVIGATION_PID_H
#define NAVIGATION_PID_H

#include <iostream>
#include <vector>
#include <chrono>
#include "opencv2/opencv.hpp"
#include "line-equation.hpp"

namespace navigation_pid
{
    cv::Mat preprocess(cv::Mat source);
    std::vector<cv::Vec4i> findLines(cv::Mat source);
    std::vector<LineEquation> findLineEquations(cv::Mat source);
    int calculateDistanceToLine(std::vector<LineEquation>);
    double calculateSteeringAngle(cv::Mat src_left, cv::Mat src_right);
    LineEquation findClosestLine(std::vector<LineEquation>);
    cv::Mat drawLines(cv::Mat, std::vector<cv::Vec4i>);
}
#endif
