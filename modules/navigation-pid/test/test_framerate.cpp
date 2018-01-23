/** 
 *  @file   test_framerate.cpp
 *  @brief  Testing script for the Framerate class
 *
 *  @author Jimmy Deng
 *  @date   2018-01-22
 */
#include <iostream>
#include "framerate.hpp"

using std::cout;
using std::endl;

int main()
{
    Framerate f;

    for (int i = 0; i < 10; ++i)
    {
        sleep(1);
        f.printFramerate();
    }
}
