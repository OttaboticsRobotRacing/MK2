#include <iostream>
#include <chrono>
#include <unistd.h>
#include "framerate.hpp"

using std::cout;
using std::endl;

using std::chrono::milliseconds;
using std::chrono::duration_cast;
using std::chrono::system_clock;

using std::chrono::high_resolution_clock;
using std::chrono::duration;
using std::chrono::microseconds;

Framerate::Framerate(): sum_(0), numberOfFrames_(0)
{
    prev_time_ = high_resolution_clock::now();
}

void Framerate::printFramerate()
{
    high_resolution_clock::time_point current_time = high_resolution_clock::now();
    //high_resolution_clock::duration elapsed = current_time - prev_time_;

    duration<double> elapsed = duration_cast<duration<double>>(current_time - prev_time_);

    prev_time_ = high_resolution_clock::now();

    //cout << 1.0 / std::chrono::duration_cast<std::chrono::milliseconds>elapsed.count() * 60000 << endl;
    //cout << std::chrono::duration_cast<std::chrono::milliseconds>elapsed.count() << endl;
    cout << "Elapsed time: " << elapsed.count() << endl;
    cout << "Framerate: " << 1.0 / elapsed.count() * 60.0 << endl;

    sum_ += (1.0 / elapsed.count() * 60.0);
    numberOfFrames_++;
}

void Framerate::printAverage()
{
    cout << "==============================\nAverage framerate: "
        << sum_ / numberOfFrames_
        << "\n=============================="
        << endl;
}
