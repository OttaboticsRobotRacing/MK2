/** 
 *  @file   navigation-pid.hpp
 *  @brief  Navigation module header using the PID strategy.
 *
 *  @author Jimmy Deng
 *  @date   2018-01-22
 */
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
    double calculateDistanceToLine(std::vector<LineEquation>, int);
    double calculateSteeringAngle(cv::Mat src_left, cv::Mat src_right);
    LineEquation findClosestLine(std::vector<LineEquation> lines);
    cv::Mat drawLines(cv::Mat, std::vector<cv::Vec4i>);
}
#endif
