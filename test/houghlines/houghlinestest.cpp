#include "opencv2/opencv.hpp"
#include <iostream>

using std::cout;
using std::cin;
using std::endl;
using std::vector;

using namespace cv;

int main()
{
    VideoCapture cap(0);
    if (!cap.isOpened())
        return -1;
    Mat src;
    cap >> src;

    Mat dst, cdst;
    Canny(src, dst, 50, 200, 3);
    cvtColor(dst, cdst, CV_GRAY2BGR);

    vector<Vec2f> lines;
    // detect lines
    HoughLines(dst, lines, 1, CV_PI/180, 150, 0, 0 );

    // draw lines
    for( size_t i = 0; i < lines.size(); i++ )
    {
        float rho = lines[i][0], theta = lines[i][1];
        Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a*rho, y0 = b*rho;
        pt1.x = cvRound(x0 + 1000*(-b));
        pt1.y = cvRound(y0 + 1000*(a));
        pt2.x = cvRound(x0 - 1000*(-b));
        pt2.y = cvRound(y0 - 1000*(a));
        line( cdst, pt1, pt2, Scalar(0,0,255), 3, CV_AA);
    }

    imshow("source", src);
    imshow("detected lines", cdst);

    waitKey();
    return 0;
}
