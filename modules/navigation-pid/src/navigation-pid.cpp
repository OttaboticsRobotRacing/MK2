#include <iostream>
#include <vector>
#include <chrono>
#include <unistd.h>
#include "opencv2/opencv.hpp"
#include "navigation-pid.hpp"

using std::cout;
using std::endl;
using std::cin;

using std::chrono::milliseconds;
using std::chrono::duration_cast;
using std::chrono::system_clock;

using std::chrono::high_resolution_clock;
using std::chrono::duration;
using std::chrono::microseconds;

namespace navigation_pid
{
    /////////////// LineEquation class ///////////////

    double LineEquation::findSlope()
    {
        double d_x = points_[2] - points_[0];
        double d_y = points_[3] - points_[1];
        return d_y / d_x;
    }
    double LineEquation::findIntercept()
    {
        double y = points_[1];
        double x = points_[0];
        return y - (m_ * x);
    }
    double LineEquation::findIntersection(int x)
    {
        double intersection = m_ * x + b_;
        if (points_[0] < points_[2])
        {
            if (x >= points_[0] && x <= points_[2])
                return intersection;
            else
                return -1;
        }
        else
        {
            if (x >= points_[2] && x <= points_[0])
                return intersection;
            else
                return -1;
        }
    }
    LineEquation::LineEquation(cv::Vec4i points): m_(0.0), b_(0.0), points_(points)
    {
        m_ = findSlope();
        b_ = findIntercept();
    }
    void LineEquation::print()
    {
        cout << "y = " << m_ << "x + " << b_ << endl;
    }
    cv::Vec4i LineEquation::getPoints()
    {
        return points_;
    }

    /////////////// LineEquation class - end ///////////////

    /////////////// PID class ///////////////

    PID::PID(double k_p, double k_i, double k_d):
        k_p_(k_p),
        k_i_(k_i),
        k_d_(k_d),
        setpoint_(0),
        error_p_(0),
        error_i_(0),
        error_d_(0),
        error_prev_(0),
        prev_time_us_(high_resolution_clock::now()),
        prev_time_ms_(time(0))
    {
        usleep(1000);
    }

    PID::~PID()
    {}

    void PID::setSetpoint(double setpoint)
    {
        setpoint_ = setpoint;
    }

    double PID::getNext(double left, double right)
    {
        // set time interval in microseconds
        high_resolution_clock::time_point currentTime = high_resolution_clock::now();
        high_resolution_clock::duration elapsed_us = currentTime - prev_time_us_;
        microseconds microsecondstest = duration_cast<microseconds>(elapsed_us);

        time_interval_ = microsecondstest.count();

        prev_time_us_ = currentTime;

        // calculate current error value
        error_p_ = right - left - setpoint_;

        // add current error to error integral
        error_i_ += error_p_;

        // calculate derivative
        error_d_ = (error_p_ - error_prev_) / static_cast<double>(time_interval_);
        error_prev_ = error_p_;

        // calculate output
        double proportional = k_p_ * error_p_;
        double integral = k_i_ * error_i_;
        double derivative = k_d_ * error_d_;

        cout << "P: " << proportional << endl;
        cout << "I: " << integral << endl;
        cout << "D: " << derivative << endl;

        double turn = proportional + integral + derivative;

        return turn;
    }

    /////////////// PID class - end ///////////////


    cv::Mat preprocess(cv::Mat source)
    {
        if (source.empty())
        {
            cout << "Could not open source image!" << endl;
            return source;
        }

        cv::Mat output;

        // check colour space
        cout << source.channels() << endl;
        if (source.channels() != 1)
        {
            cout << "Converting image to greyscale" << endl;
        }
        // convert to greyscale if source isn't already


        // apply a bit of blur to remove high frequency noise
        cv::cvtColor(source, output, cv::COLOR_BGR2GRAY);
        cv::GaussianBlur(output, output, cv::Size(7,7), 1.5, 1.5);
        // cv::Canny(output, output, 0, 30, 3);

        // return processed image
        return output;
    }

    std::vector<cv::Vec4i> findLines(cv::Mat source)
    {
        std::vector<cv::Vec4i> lines;
        cv::Mat mask;

        cv::Canny(source, mask, 100, 200, 3);

        cv::HoughLinesP(mask, lines, 1, CV_PI / 180, 50, 60, 5);

        cout << "Vector size: " << lines.size() << endl;

        return lines;
    }

    std::vector<LineEquation> findLineEquations(cv::Mat source)
    {
        std::vector<cv::Vec4i> lines = findLines(source);
        std::vector<navigation_pid::LineEquation> line_equations;

        for (auto i : lines)
        {
            line_equations.push_back(navigation_pid::LineEquation(i));
        }
        return line_equations;
    }

    int calculateDistanceToLine(std::vector<LineEquation>)
    {
        return -1;
    }

    double calculateSteeringAngle(cv::Mat src_left, cv::Mat src_right)
    {
        return -1;
    }
}
