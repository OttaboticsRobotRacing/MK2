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

class Framerate
{
    high_resolution_clock::time_point prev_time_;
    long double sum_;
    long int numberOfFrames_;
public:
    Framerate();
    void printFramerate();
    void printAverage();
};



#endif
