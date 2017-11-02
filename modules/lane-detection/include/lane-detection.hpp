#ifndef LANE_DETECTION_H
#define LANE_DETECTION_H

#include <iostream>
#include <vector>
#include "opencv2/opencv.hpp"

namespace lane_detection
{
    class LineEquation
    {
    private:
        double m_;
        double b_;
        cv::Vec4i points_;

        double findSlope();
        double findIntercept();

    public:
        LineEquation(cv::Vec4i);
        double findIntersection(int x);
        void print();
        cv::Vec4i getPoints();

    };



cv::Mat preprocess(cv::Mat source);
std::vector<cv::Vec4i> findLines(cv::Mat source);



}
#endif
