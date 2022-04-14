#include "RateCounter.h"

using namespace engine;

void RateCounter::inc() {
    using namespace common::time;
    ++counter_;
    auto elapsed_secs = Duration::from(start_time_).value(TimeUnit::SECONDS);
    if (elapsed_secs > 0) {
        auto hertz = float(counter_) / float(elapsed_secs);
        if (hertz < 10000) {
            constexpr float smoothing_prev = 0.9f;
            constexpr float smoothing_cur = 1.0f - smoothing_prev;
            prev_hertz_ = cur_hertz_;
            cur_hertz_ = (prev_hertz_ * smoothing_prev) + (hertz * smoothing_cur);
        }
    }
}

auto RateCounter::hertz() const -> float {
    return cur_hertz_;
}
