#include <iostream>
#include <vector>
#include "opencv2/opencv.hpp"
#include "lane-detection.hpp"

using std::cout;
using std::endl;
using std::cin;

namespace lane_detection
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
}
