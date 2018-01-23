/** 
 *  @file   line-equation.hpp
 *  @brief  Equation of a line.
 *
 *  @author Jimmy Deng
 *  @date   2018-01-22
 */

#ifndef LINE_EQUATION_H
#define LINE_EQUATION_H

#include "opencv2/opencv.hpp"

namespace navigation_pid
{
    class LineEquation
    {
    private:
        double m_; //!< Slope
        double b_; //!< y-intercept
        cv::Vec4i points_; //!< Endpoints of the line

        double findSlope();
        double findIntercept();

    public:
        LineEquation(cv::Vec4i);
        double findIntersection(int x);
        void print();
        cv::Vec4i getPoints();
    };
}
#endif
