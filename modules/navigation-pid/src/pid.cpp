#include <iostream>
#include <chrono>
#include <unistd.h>
#include "pid.hpp"

namespace navigation_pid
{
    PID::PID(double k_p, double k_i, double k_d):
        k_p_(k_p),
        k_i_(k_i),
        k_d_(k_d),
        setpoint_(0),
        error_p_(0),
        error_i_(0),
        error_d_(0),
        error_prev_(0),
        prev_time_us_(high_resolution_clock::now()),
        prev_time_ms_(time(0))
    {
        usleep(1000);
    }

    PID::~PID()
    {}

    void PID::setSetpoint(double setpoint)
    {
        setpoint_ = setpoint;
    }

    double PID::getNext(double left, double right)
    {
        // set time interval in microseconds
        high_resolution_clock::time_point currentTime = high_resolution_clock::now();
        high_resolution_clock::duration elapsed_us = currentTime - prev_time_us_;
        microseconds microsecondstest = duration_cast<microseconds>(elapsed_us);

        time_interval_ = microsecondstest.count();

        prev_time_us_ = currentTime;

        // calculate current error value
        error_p_ = right - left - setpoint_;

        // add current error to error integral
        error_i_ += error_p_;

        // calculate derivative
        error_d_ = (error_p_ - error_prev_) / static_cast<double>(time_interval_);
        error_prev_ = error_p_;

        // calculate output
        double proportional = k_p_ * error_p_;
        double integral = k_i_ * error_i_;
        double derivative = k_d_ * error_d_;

        cout << "P: " << proportional << endl;
        cout << "I: " << integral << endl;
        cout << "D: " << derivative << endl;

        double turn = proportional + integral + derivative;

        return turn;
    }
}
