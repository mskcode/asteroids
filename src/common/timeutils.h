#ifndef COMMON_UTILS_TIME_H
#define COMMON_UTILS_TIME_H

#include <chrono>
#include <cstdint>

namespace common::time {

enum TimeUnit {
    NANOSECONDS,
    MICROSECONDS,
    MILLISECONDS,
    SECONDS,
    MINUTES,
    HOURS,
};

class Instant final {
public:
    Instant(const Instant& other) = default;
    Instant(Instant&& other) = default;
    ~Instant() = default;

    auto operator=(const Instant& rhs) -> Instant& = default;
    auto operator=(Instant&& rhs) -> Instant& = default;

    static auto now() -> Instant;

    [[nodiscard]] auto nanosecond_value() const -> int64_t;
    [[nodiscard]] auto value(TimeUnit time_unit) const -> int64_t;

private:
    // nanosecond precision requires at least 64bit integer: https://en.cppreference.com/w/cpp/chrono/duration
    // std::chrono::time_point_t.time_since_epoch.count() returns a signed value, that's why epoch_ns_ is also defined
    // as such
    int64_t epoch_ns_;

    Instant(int64_t epoch_ns);
};

class Duration final {
public:
    Duration(const Duration& other) = default;
    Duration(Duration&& other) = default;
    ~Duration() = default;

    auto operator=(const Duration& rhs) -> Duration& = default;
    auto operator=(Duration&& rhs) -> Duration& = default;

    static auto between(Instant start, Instant end) -> Duration;

    [[nodiscard]] auto nanosecond_value() const -> int64_t;
    [[nodiscard]] auto value(TimeUnit time_unit) const -> int64_t;

private:
    int64_t duration_ns_;

    Duration(int64_t duration_ns);
};

} // namespace common::time

#endif // COMMON_UTILS_TIME_H
