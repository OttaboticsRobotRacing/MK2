#include <iostream>
#include "opencv2/opencv.hpp"
#include "navigation-pid.hpp"
#include "line-equation.hpp"
#include "framerate.hpp"

using std::cout;
using std::endl;
using std::cin;

using namespace cv;

int main()
{
    cout << "test" << endl;
    cout << "opencv version: " << CV_VERSION << endl;

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

    for (;;)
    {
        if (usingWebcam)
        {
            camera_left >> frame_left;
            camera_right >> frame_right;

            // frame = navigation_pid::preprocess(frame_left);
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
        for (auto i : line_equations_left)
        {
            int y = i.findIntersection(x_left);

            // check if intercept is in the image
            if (y >= 0 && y < frame_left.rows)
            {
                cv::Vec4i points = i.getPoints();
                line(frame_left, cv::Point(points[0], points[1]), cv::Point(points[2], points[3]), cv::Scalar(255, 0, 255), 2, LINE_AA);
                circle(frame_left, cv::Point(x_left, y), 3, cv::Scalar(0, 0, 255), 2);
            }
        }

        for (auto i : line_equations_right)
        {
            int y = i.findIntersection(x_right);

            // check if intercept is in the image
            if (y >= 0 && y < frame_right.rows)
            {
                cv::Vec4i points = i.getPoints();
                line(frame_right, cv::Point(points[0], points[1]), cv::Point(points[2], points[3]), cv::Scalar(255, 0, 255), 2, LINE_AA);
                circle(frame_right, cv::Point(x_right, y), 3, cv::Scalar(0, 0, 255), 2);
            }
        }


        //cout << "Line: " << lines[0] << endl;
        //cout << "Line eq size: " << line_equations.size() << endl;

        //line_equations[0].print();

        imshow("left_window", frame_left);
        imshow("right_window", frame_right);

        //sleep(1);

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
