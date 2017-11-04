#include <iostream>
#include "opencv2/opencv.hpp"
#include "navigation-pid.hpp"

using std::cout;
using std::endl;
using std::cin;

using namespace cv;

int main()
{
    cout << "test" << endl;
    cout << "opencv version: " << CV_VERSION << endl;

    /*
    VideoCapture cap(0);
    if (!cap.isOpened())
    {
        cout << "No video device" << endl;
        return -1;
    }
    */

    Mat edges, frame;
    namedWindow("edges", 1);

    frame = imread("temp/road_01.jpg", 1);


    for (;;)
    {
        //Mat frame;
        //cap >> frame;
        //cvtColor(frame, edges, COLOR_BGR2GRAY);
        //GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
        //Canny(edges, edges, 0, 30, 3);

        frame = navigation_pid::preprocess(frame);

        cv::cvtColor(frame, frame, cv::COLOR_GRAY2BGR);

        std::vector<cv::Vec4i> lines = navigation_pid::findLines(frame);
        std::vector<navigation_pid::LineEquation> line_equations;

        for (size_t i = 0; i < lines.size(); ++i)
        {
            cv::Vec4i l = lines[i];
            line(frame, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]), cv::Scalar(0, 255, 0), 2, LINE_AA);
            circle(frame, cv::Point(l[0], l[1]), 3, cv::Scalar(255, 0, 0), 2);
            circle(frame, cv::Point(l[2], l[3]), 3, cv::Scalar(255, 0, 0), 2);
            line_equations.push_back(navigation_pid::LineEquation(l));
        }

        int x = frame.cols / 2;
        line(frame, cv::Point(x, 0), cv::Point(x, frame.rows - 1), cv::Scalar(127, 127, 127), 1, LINE_AA);

        for (auto i : line_equations)
        {
            int y = i.findIntersection(x);

            if (y >= 0 && y < frame.rows)
            {
                cv::Vec4i points = i.getPoints();
                line(frame, cv::Point(points[0], points[1]), cv::Point(points[2], points[3]), cv::Scalar(255, 0, 255), 2, LINE_AA);
                circle(frame, cv::Point(x, y), 3, cv::Scalar(0, 0, 255), 2);
            }
        }


        cout << "Line: " << lines[0] << endl;
        cout << "Line eq size: " << line_equations.size() << endl;

        line_equations[0].print();

        imshow("edges", frame);

        /*
        if(waitKey(30) == 27)
        {
            cout << "Breaking" << endl;
            break; // exit by pressing esc, value can by found on asciitable.com under Dec column
        }
        */
        waitKey(0);
        break;
    }

    return 0;
}
