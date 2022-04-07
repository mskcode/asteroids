#include "TickLimiter.h"

using namespace asteroids;
using namespace common::time;

TickLimiter::TickLimiter(uint64_t target_ticks_per_second) :
    target_minimum_tick_duration_(Duration::of(convert_seconds(1, TimeUnit::NANOSECONDS) / target_ticks_per_second)),
    last_tick_(Instant::of(0)) {}

void TickLimiter::tick() {
    last_tick_ = Instant::now();
}

auto TickLimiter::should_tick() const -> bool {
    auto elapsed = Duration::from(last_tick_);
    return elapsed >= target_minimum_tick_duration_;
}
