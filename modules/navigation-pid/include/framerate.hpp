/** 
 *  @file   framerate.hpp
 *  @brief  Framerate counter header file.
 *
 *  @author Jimmy Deng
 *  @date   2018-01-22
 */
#ifndef FRAMERATE_H
#define FRAMERATE_H

#include <iostream>
#include <chrono>
#include <unistd.h>

using std::chrono::milliseconds;
using std::chrono::duration_cast;
using std::chrono::system_clock;

using std::chrono::high_resolution_clock;
using std::chrono::duration;
using std::chrono::microseconds;

/**
 *  @class  Framerate
 * 
 *  @brief  Framerate counter class.
 * 
 */
class Framerate
{
    high_resolution_clock::time_point prev_time_; //!< The time for the last frame; used to find frame duration.
    long double sum_; //!< Running total of the framerate to get an average.
    long int numberOfFrames_; //!< Running total of elapsed frames.
public:
    Framerate();
    void printFramerate();
    void printAverage();
};



#endif
