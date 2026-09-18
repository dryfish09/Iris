#pragma once

#include <chrono>

namespace iris::util {
    struct timer_t {
    private:
        using clock = std::chrono::steady_clock;
        template<typename Clock>
        using time_point = std::chrono::time_point<Clock>;

        time_point<clock> start_time;
        time_point<clock> end_time;

        bool ended = false;

        clock::duration elapsed();
    public:
        timer_t(bool start = true);
        void start();
        void stop();
        double ms();
        double us();
        double sec();
        double min();
        double hr();
        enum class unit_flag_t : uint8_t {
            us   = 0b10000000,
            ms   = 0b01000000,
            sec  = 0b00100000,
            min  = 0b00010000,
            hr   = 0b00001000,
            day  = 0b00000100,
            all  = 0b11111100,
        };
        std::string to_str(unit_flag_t flags = unit_flag_t::all);
    };

    void wait_for(double seconds) noexcept;
}
