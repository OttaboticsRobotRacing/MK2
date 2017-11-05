#include <iostream>
#include "line-equation.hpp"
#include "opencv2/opencv.hpp"

using std::cout;
using std::endl;

namespace navigation_pid
{
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
}
