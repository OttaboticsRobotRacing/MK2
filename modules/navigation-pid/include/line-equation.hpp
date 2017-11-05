#ifndef LINE_EQUATION_H
#define LINE_EQUATION_H

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
}
#endif
