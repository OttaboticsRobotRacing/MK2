#ifndef NAVIGATION_PID_H
#define NAVIGATION_PID_H

#include <iostream>
#include <vector>
#include <chrono>
#include "opencv2/opencv.hpp"

namespace navigation_pid
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

    class PID
    {
    public:
        PID(double k_p, double k_i, double k_d);
        ~PID();
        void setSetpoint(double setpoint);
        double getNext(double left, double right);

    private:
        double k_p_;
        double k_i_;
        double k_d_;
        double setpoint_;

        double error_p_;
        double error_i_;
        double error_d_;
        double error_prev_;

        std::chrono::high_resolution_clock::time_point prev_time_us_;
        time_t time_interval_;
        time_t prev_time_ms_;
    };

    cv::Mat preprocess(cv::Mat source);
    std::vector<cv::Vec4i> findLines(cv::Mat source);
    std::vector<LineEquation> findLineEquations(cv::Mat source);
    int calculateDistanceToLine(std::vector<LineEquation>);
    double calculateSteeringAngle(cv::Mat src_left, cv::Mat src_right);


}
#endif
