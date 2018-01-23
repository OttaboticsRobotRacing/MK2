/** 
 *  @file   test.cpp
 *  @brief  Sample main file
 *
 *  @author Jimmy Deng
 *  @date   2018-01-22
 */
#include <iostream>
#include "opencv2/opencv.hpp"
#include "sample.hpp"

using std::cout;
using std::endl;
using std::cin;

/**
     *  Sample main function
     *
     *  @brief  Sample main function
     *  @author Jimmy Deng
     *  @date   2018-01-22
     */
int main()
{
    cout << "test" << endl;
    cout << "opencv version: " << CV_VERSION << endl;

    sample_function();

    return 0;
}
