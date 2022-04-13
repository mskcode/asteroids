#include "timeutils.h"
#include <stdexcept>

using namespace common::time;

const Instant Instant::UnixEpoch{0};

Instant::Instant(uint64_t epoch_ns) :
    epoch_ns_(epoch_ns) {}

auto Instant::of(uint64_t nanos, TimeUnit time_unit) -> Instant {
    return {convert_nanoseconds(nanos, time_unit)};
}

auto Instant::now() -> Instant {
    using namespace std::chrono;
    auto time_point_now = high_resolution_clock::now();
    auto time_point_ns = time_point_cast<nanoseconds>(time_point_now);
    auto value = time_point_ns.time_since_epoch().count();
    return {static_cast<uint64_t>(value)};
}

auto Instant::nanosecond_value() const -> uint64_t {
    return epoch_ns_;
}

auto Instant::value(TimeUnit time_unit) const -> uint64_t {
    return convert_nanoseconds(epoch_ns_, time_unit);
}

Duration::Duration(uint64_t duration_ns) :
    duration_ns_(duration_ns) {}

auto Duration::between(Instant start, Instant end) -> Duration {
    return end.nanosecond_value() > start.nanosecond_value() ?
               Duration(end.nanosecond_value() - start.nanosecond_value()) :
               Duration(start.nanosecond_value() - end.nanosecond_value());
}

auto Duration::from(Instant start) -> Duration {
    return Duration::between(start, Instant::now());
}

auto Duration::of(uint64_t nanos, TimeUnit time_unit) -> Duration {
    return {convert_nanoseconds(nanos, time_unit)};
}

auto Duration::nanosecond_value() const -> uint64_t {
    return duration_ns_;
}

auto Duration::value(TimeUnit time_unit) const -> uint64_t {
    return convert_nanoseconds(duration_ns_, time_unit);
}

auto common::time::operator==(const Duration& lhs, const Duration& rhs) -> bool {
    return lhs.nanosecond_value() == rhs.nanosecond_value();
}

auto common::time::operator!=(const Duration& lhs, const Duration& rhs) -> bool {
    return lhs.nanosecond_value() != rhs.nanosecond_value();
}

auto common::time::operator<(const Duration& lhs, const Duration& rhs) -> bool {
    return lhs.nanosecond_value() < rhs.nanosecond_value();
}

auto common::time::operator>(const Duration& lhs, const Duration& rhs) -> bool {
    return lhs.nanosecond_value() > rhs.nanosecond_value();
}

auto common::time::operator<=(const Duration& lhs, const Duration& rhs) -> bool {
    return lhs.nanosecond_value() <= rhs.nanosecond_value();
}

auto common::time::operator>=(const Duration& lhs, const Duration& rhs) -> bool {
    return lhs.nanosecond_value() >= rhs.nanosecond_value();
}

StopWatch::StopWatch(Instant start_time) :
    start_time_(start_time) {}

auto StopWatch::start() -> StopWatch {
    return {Instant::now()};
}

auto StopWatch::split() -> Duration {
    return Duration::from(start_time_);
}
