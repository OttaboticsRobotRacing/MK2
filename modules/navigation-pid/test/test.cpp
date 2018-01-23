/** 
 *  @file   test.cpp
 *  @brief  Testing script for the PID navigation strategy
 *
 *  @author Jimmy Deng
 *  @date   2018-01-22
 */
#include <iostream>
#include "opencv2/opencv.hpp"
#include "navigation-pid.hpp"
#include "line-equation.hpp"
#include "pid.hpp"
#include "framerate.hpp"

using std::cout;
using std::endl;
using std::cin;

using namespace cv;

int main()
{
    cout << "test" << endl;
    cout << "opencv version: " << CV_VERSION << endl;

    // download the test image into temp/road_01.jpg
    if (!std::ifstream("temp/road_01.jpg"))
    {
        cout << "Test file does not exist... Downloading..." << endl;
        system("mkdir -p temp");
        system("wget -O temp/road_01.jpg http://static-15.sinclairstoryline.com/resources/media/305d4c9b-92d5-48d8-a562-188442d31a47-large16x9_ThinkstockPhotos506008882.jpg?1493652604697");
    }

    Mat frame_left, frame_right;
    namedWindow("left_window", 1);
    namedWindow("right_window", 1);

    bool usingWebcam = false;

    VideoCapture camera_left(0), camera_right(2);
    if (!camera_left.isOpened() || !camera_right.isOpened())
    {
        //cout << "No video device! Exiting..." << endl;
        //return -1;
        cout << "No video device! Using an image instead..." << endl;
        frame_left = imread("temp/road_01.jpg", 1);
        frame_right = imread("temp/road_01.jpg", 1);

        frame_left = navigation_pid::preprocess(frame_left);
        frame_right = navigation_pid::preprocess(frame_right);

        cv::cvtColor(frame_left, frame_left, cv::COLOR_GRAY2BGR);
        cv::cvtColor(frame_right, frame_right, cv::COLOR_GRAY2BGR);
    }
    else
    {
        usingWebcam = true;
    }

    Framerate framerate;

    navigation_pid::PID pid(1, 0.5, 0.5);

    for (;;)
    {
        if (usingWebcam)
        {
            camera_left >> frame_left;
            camera_right >> frame_right;

            frame_left = navigation_pid::preprocess(frame_left);
            frame_right = navigation_pid::preprocess(frame_right);

            cv::cvtColor(frame_left, frame_left, cv::COLOR_GRAY2BGR);
            cv::cvtColor(frame_right, frame_right, cv::COLOR_GRAY2BGR);
        }

        // find lines and their respective equations
        std::vector<cv::Vec4i> lines_left = navigation_pid::findLines(frame_left);
        std::vector<navigation_pid::LineEquation> line_equations_left = navigation_pid::findLineEquations(frame_left);

        std::vector<cv::Vec4i> lines_right = navigation_pid::findLines(frame_right);
        std::vector<navigation_pid::LineEquation> line_equations_right = navigation_pid::findLineEquations(frame_right);

        // draw lines onto the frame
        frame_left = navigation_pid::drawLines(frame_left, lines_left);
        frame_right = navigation_pid::drawLines(frame_right, lines_right);

        // vertical middle line
        int x_left = frame_left.cols / 2;
        line(frame_left, cv::Point(x_left, 0), cv::Point(x_left, frame_left.rows - 1), cv::Scalar(127, 127, 127), 1, LINE_AA);

        int x_right = frame_right.cols / 2;
        line(frame_right, cv::Point(x_right, 0), cv::Point(x_right, frame_right.rows - 1), cv::Scalar(127, 127, 127), 1, LINE_AA);

        // check intercepts for list of lines

        std::vector<navigation_pid::LineEquation> valid_line_equations_left;
        std::vector<navigation_pid::LineEquation> valid_line_equations_right;

        for (auto i : line_equations_left)
        {
            int y = i.findIntersection(x_left);

            // check if intercept is in the image
            if (y >= 0 && y < frame_left.rows)
            {
                // display lines which intersect
                cv::Vec4i points = i.getPoints();
                line(frame_left, cv::Point(points[0], points[1]), cv::Point(points[2], points[3]), cv::Scalar(255, 0, 255), 2, LINE_AA);
                circle(frame_left, cv::Point(x_left, y), 3, cv::Scalar(0, 0, 255), 2);
                valid_line_equations_left.push_back(i);
            }
        }

        for (auto i : line_equations_right)
        {
            int y = i.findIntersection(x_right);

            // check if intercept is in the image
            if (y >= 0 && y < frame_right.rows)
            {
                // display lines which intersect
                cv::Vec4i points = i.getPoints();
                line(frame_right, cv::Point(points[0], points[1]), cv::Point(points[2], points[3]), cv::Scalar(255, 0, 255), 2, LINE_AA);
                circle(frame_right, cv::Point(x_right, y), 3, cv::Scalar(0, 0, 255), 2);
                valid_line_equations_right.push_back(i);
            }
        }

        double left_distance = calculateDistanceToLine(valid_line_equations_left, x_left);
        double right_distance = calculateDistanceToLine(valid_line_equations_right, x_right);

        if (left_distance == -1)
            left_distance = 0;
        if (right_distance == -1)
            right_distance = 0;

        circle(frame_left, cv::Point(x_left, left_distance), 5, cv::Scalar(255, 255, 0), 2);
        circle(frame_right, cv::Point(x_right, right_distance), 5, cv::Scalar(255, 255, 0), 2);

        cout << "Left distance: " << left_distance << endl;
        cout << "Right distance: " << right_distance << endl;

        cout << "PID: " << pid.getNext(frame_left.rows - left_distance, frame_right.rows - right_distance) << endl;


        imshow("left_window", frame_left);
        imshow("right_window", frame_right);

        framerate.printFramerate();

        if(waitKey(30) == 27)
        {
            framerate.printAverage();
            cout << "Breaking" << endl;
            break; // exit by pressing esc, value can by found on asciitable.com under Dec column
        }

        if (!usingWebcam)
        {
            waitKey(0);
            break;
        }
    }

    return 0;
}
