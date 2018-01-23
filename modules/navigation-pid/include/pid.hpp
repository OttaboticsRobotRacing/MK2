/** 
 *  @file   pid.hpp
 *  @brief  PID controller for two distance inputs.
 *
 *  @author Jimmy Deng
 *  @date   2018-01-22
 */
#ifndef PID_H
#define PID_H

/**
 *  @namespace  navigation_pid
 * 
 *  @brief      Namespace for the PID steering strategy.
 * 
 */
namespace navigation_pid
{
    class PID
    {
    public:
        PID(double k_p, double k_i, double k_d);
        ~PID();
        void setSetpoint(double setpoint);
        double getNext(double left, double right);

    private:
        double k_p_; //!< Proportional constant
        double k_i_; //!< Integral constant
        double k_d_; //!< Derivative constant
        double setpoint_; //!< Setpoint

        double error_p_; //!< Proportional error
        double error_i_; //!< Integral error
        double error_d_; //!< Derivative error
        double error_prev_; //!< Previous error

        std::chrono::high_resolution_clock::time_point prev_time_us_; //!< Time value in us for previous output; used to measure elapsed time
        time_t time_interval_; //!< Time interval
        time_t prev_time_ms_; //!< Time value in ms for previous output; used to measure elapsed time
    };
}

#endif
