/** 
 *  @file   line-equation.cpp
 *  @brief  Equation of a line.
 *
 *  @author Jimmy Deng
 *  @date   2018-01-22
 */
#include <iostream>
#include "line-equation.hpp"
#include "opencv2/opencv.hpp"

using std::cout;
using std::endl;

/**
 *  @namespace  navigation_pid
 * 
 *  @brief      Namespace for the PID steering strategy.
 * 
 */
namespace navigation_pid
{
    /**
     *  @brief  Returns slope of a line.
     *  @author Jimmy Deng
     *  @date   2018-01-22
     */
    double LineEquation::findSlope()
    {
        double d_x = points_[2] - points_[0];
        double d_y = points_[3] - points_[1];
        return d_y / d_x;
    }

    /**
     *  @brief  Returns y-intercept of a line.
     *  @author Jimmy Deng
     *  @date   2018-01-22
     */
    double LineEquation::findIntercept()
    {
        double y = points_[1];
        double x = points_[0];
        return y - (m_ * x);
    }

    /**
     *  @brief  Returns intercept of the line with a vertical line at x.
     *  @author Jimmy Deng
     *  @param  x Vertical line at x.
     *  @date   2018-01-22
     */
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

    /**
     *  @brief  LineEquation contructor.
     *  @author Jimmy Deng
     *  @date   2018-01-22
     */
    LineEquation::LineEquation(cv::Vec4i points): m_(0.0), b_(0.0), points_(points)
    {
        m_ = findSlope();
        b_ = findIntercept();
    }
    
    /**
     *  @brief  Prints equation of the line.
     *  @author Jimmy Deng
     *  @date   2018-01-22
     */
    void LineEquation::print()
    {
        cout << "y = " << m_ << "x + " << b_ << endl;
    }

    /**
     *  @brief  Getter function for the endpoints.
     *  @author Jimmy Deng
     *  @date   2018-01-22
     */
    cv::Vec4i LineEquation::getPoints()
    {
        return points_;
    }
}
