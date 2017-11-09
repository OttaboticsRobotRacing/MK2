#include <iostream>
#include <vector>
#include "opencv2/opencv.hpp"
#include "navigation-pid.hpp"
#include "line-equation.hpp"

using std::cout;
using std::endl;
using std::cin;

namespace navigation_pid
{

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
        std::vector<LineEquation> line_equations;

        for (auto i : lines)
        {
            line_equations.push_back(LineEquation(i));
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

    LineEquation findClosestLine(std::vector<LineEquation> lines)
    {
        return lines[0];
    }

    cv::Mat drawLines(cv::Mat frame, std::vector<cv::Vec4i> lines)
    {
        for (size_t i = 0; i < lines.size(); ++i)
        {
            cv::Vec4i l = lines[i];
            line(frame, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]), cv::Scalar(0, 255, 0), 2, cv::LINE_AA);
            circle(frame, cv::Point(l[0], l[1]), 3, cv::Scalar(255, 0, 0), 2);
            circle(frame, cv::Point(l[2], l[3]), 3, cv::Scalar(255, 0, 0), 2);
        }
        return frame;
    }
}
