/** 
 *  @file   navigation-pid.cpp
 *  @brief  Navigation module using the PID strategy.
 *
 *  @author Jimmy Deng
 *  @date   2018-01-22
 */
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
    /**
     *  Applies preprocessing filters to an image including:
     *  - BGR to greyscale colour space conversion
     *  - Apply a light Gaussian blur 
     *
     *  @brief  Applies preprocessing filters to images.
     *  @author Jimmy Deng
     *  @param  source Source image.
     *  @date   2018-01-22
     */
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

    /** 
     *  Finds all straight line endpoints using HoughLines and returns a vector containing them.
     * 
     *  @brief  Returns vector of straight line endpoints.
     *  @author Jimmy Deng
     *  @param  source Source image.
     *  @date   2018-01-22
     */
    std::vector<cv::Vec4i> findLines(cv::Mat source)
    {
        std::vector<cv::Vec4i> lines;
        cv::Mat mask;

        cv::Canny(source, mask, 100, 200, 3);

        cv::HoughLinesP(mask, lines, 1, CV_PI / 180, 50, 60, 5);

        cout << "Vector size: " << lines.size() << endl;

        return lines;
    }

    /**
     *  Converts an image into a vector of LineEquations.
     * 
     *  @brief  Returns vector of LineEquations.
     *  @author Jimmy Deng
     *  @param  source Source image.
     *  @date   2018-01-22
     */
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

    /**
     *  Returns shortest distance between the lower edge of the frame at x and a vector of LineEquations.
     *
     *  @brief  
     *  @author Jimmy Deng
     *  @param  line_equations Vector of LineEquations
     *  @param  x Vertical line, at x
     *  @date   2018-01-22
     */
    double calculateDistanceToLine(std::vector<LineEquation> line_equations, int x)
    {
        if (line_equations.size() <= 0)
        {
            return -1;
        }

        LineEquation shortestLine = line_equations[0];
        double distance = shortestLine.findIntersection(x);

        for (auto i : line_equations)
        {
            if (i.findIntersection(x) > distance) // 0 pixel coord at the top, increases as you go down
            {
                shortestLine = i;
                distance = i.findIntersection(x);
            }
        }
        return distance;
    }

    /**
     *  WIP 
     * 
     *  @brief  WIP - Returns output steering angle.
     *  @author Jimmy Deng
     *  @param  src_left Left source image
     *  @param  src_right Right source image
     *  @date   2018-01-22
     */
    double calculateSteeringAngle(cv::Mat src_left, cv::Mat src_right)
    {
        return -1;
    }

    /**
     *  
     *
     *  @brief  Not sure what this is supposed to do...
     *  @author Jimmy Deng
     *  @param  lines Vector of LineEquations
     *  @date   2018-01-22
     */
    LineEquation findClosestLine(std::vector<LineEquation> lines)
    {
        //TODO: need to handle case where no lines are detected
        return lines[0];
    }

    /**
     *  
     *
     *  @brief  Draws every line in lines onto the frame.  
     *  @author Jimmy Deng
     *  @param  frame Source image
     *  @param  lines Vector of line endpoints.
     *  @date   2018-01-22
     */
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
