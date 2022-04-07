#include "timeutils.h"
#include <stdexcept>

using namespace common::time;

constexpr auto convert_nanoseconds(int64_t value, TimeUnit time_unit) -> int64_t {
    switch (time_unit) {
    case TimeUnit::NANOSECONDS:
        return value;
    case TimeUnit::MICROSECONDS:
        return value / 1000;
    case TimeUnit::MILLISECONDS:
        return value / 1000000;
    case TimeUnit::SECONDS:
        return value / 1000000000;
    case TimeUnit::MINUTES: // TODO implement me
    case TimeUnit::HOURS:   // TODO implement me
    default:
        throw std::runtime_error("Unsupported time unit");
    }
}

Instant::Instant(int64_t epoch_ns) :
    epoch_ns_(epoch_ns) {}

auto Instant::now() -> Instant {
    using namespace std::chrono;
    auto time_point_now = high_resolution_clock::now();
    auto time_point_ns = time_point_cast<nanoseconds>(time_point_now);
    auto value = time_point_ns.time_since_epoch().count();
    return {value};
}

auto Instant::nanosecond_value() const -> int64_t {
    return epoch_ns_;
}

auto Instant::value(TimeUnit time_unit) const -> int64_t {
    return convert_nanoseconds(epoch_ns_, time_unit);
}

Duration::Duration(int64_t duration_ns) :
    duration_ns_(duration_ns) {}

auto Duration::between(Instant start, Instant end) -> Duration {
    return end.nanosecond_value() > start.nanosecond_value() ?
               Duration(end.nanosecond_value() - start.nanosecond_value()) :
               Duration(start.nanosecond_value() - end.nanosecond_value());
}

auto Duration::nanosecond_value() const -> int64_t {
    return duration_ns_;
}

auto Duration::value(TimeUnit time_unit) const -> int64_t {
    return convert_nanoseconds(duration_ns_, time_unit);
}
