#ifndef PID_H
#define PID_H

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
        double k_p_;
        double k_i_;
        double k_d_;
        double setpoint_;

        double error_p_;
        double error_i_;
        double error_d_;
        double error_prev_;

        std::chrono::high_resolution_clock::time_point prev_time_us_;
        time_t time_interval_;
        time_t prev_time_ms_;
    };
}

#endif
