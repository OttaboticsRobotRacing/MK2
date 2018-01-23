/** 
 *  @file   sample.cpp
 *  @brief  Sample code
 *
 *  @author Jimmy Deng
 *  @date   2018-01-22
 */
#include <iostream>
#include "opencv2/opencv.hpp"

using std::cout;
using std::endl;
using std::cin;

/**
 *  @namespace  sample
 * 
 *  @brief      Sample namespace
 * 
 */
namespace sample
{
    /**
     *  Sample function
     *
     *  @brief  Sample function
     *  @author Jimmy Deng
     *  @date   2018-01-22
     */
    void sample_function()
    {
        cout << "sample_function" << endl;
        cout << "opencv version: " << CV_VERSION << endl;
    }
}
