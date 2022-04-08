#ifndef COMMON_TIME_H
#define COMMON_TIME_H

#include <chrono>
#include <cstdint>
#include <stdexcept>

namespace common::time {

enum TimeUnit {
    NANOSECONDS,
    MICROSECONDS,
    MILLISECONDS,
    SECONDS,
    MINUTES,
    HOURS,
};

constexpr auto convert_seconds(uint64_t seconds, TimeUnit time_unit) -> uint64_t {
    switch (time_unit) {
    case TimeUnit::NANOSECONDS:
        return seconds * 1000000000;
    case TimeUnit::MICROSECONDS:
        return seconds * 1000000;
    case TimeUnit::MILLISECONDS:
        return seconds * 1000;
    case TimeUnit::SECONDS:
        return seconds;
    case TimeUnit::MINUTES:
        return seconds / 60;
    case TimeUnit::HOURS:
        return seconds / 3600;
    default:
        throw std::runtime_error("Unsupported time unit");
    }
}

constexpr auto convert_nanoseconds(uint64_t nanos, TimeUnit time_unit) -> uint64_t {
    switch (time_unit) {
    case TimeUnit::NANOSECONDS:
        return nanos;
    case TimeUnit::MICROSECONDS:
        return nanos / 1000;
    case TimeUnit::MILLISECONDS:
        return nanos / 1000000;
    case TimeUnit::SECONDS:
        return nanos / 1000000000;
    case TimeUnit::MINUTES:
        return nanos / 60000000000;
    case TimeUnit::HOURS:
        return nanos / 3600000000000;
    default:
        throw std::runtime_error("Unsupported time unit");
    }
}

class Instant final {
public:
    Instant(const Instant& other) = default;
    Instant(Instant&& other) = default;
    ~Instant() = default;

    auto operator=(const Instant& rhs) -> Instant& = default;
    auto operator=(Instant&& rhs) -> Instant& = default;

    static auto of(uint64_t nanos, TimeUnit time_unit = TimeUnit::NANOSECONDS) -> Instant;
    static auto now() -> Instant;

    [[nodiscard]] auto nanosecond_value() const -> uint64_t;
    [[nodiscard]] auto value(TimeUnit time_unit) const -> uint64_t;

private:
    uint64_t epoch_ns_ = 0;

    Instant(uint64_t epoch_ns);
};

class Duration final {
public:
    Duration(const Duration& other) = default;
    Duration(Duration&& other) = default;
    ~Duration() = default;

    auto operator=(const Duration& rhs) -> Duration& = default;
    auto operator=(Duration&& rhs) -> Duration& = default;

    friend auto operator==(const Duration& lhs, const Duration& rhs) -> bool;
    friend auto operator!=(const Duration& lhs, const Duration& rhs) -> bool;
    friend auto operator<(const Duration& lhs, const Duration& rhs) -> bool;
    friend auto operator>(const Duration& lhs, const Duration& rhs) -> bool;
    friend auto operator<=(const Duration& lhs, const Duration& rhs) -> bool;
    friend auto operator>=(const Duration& lhs, const Duration& rhs) -> bool;

    static auto between(Instant start, Instant end) -> Duration;
    static auto from(Instant start) -> Duration;
    static auto of(uint64_t nanos, TimeUnit time_unit = TimeUnit::NANOSECONDS) -> Duration;

    [[nodiscard]] auto nanosecond_value() const -> uint64_t;
    [[nodiscard]] auto value(TimeUnit time_unit) const -> uint64_t;

private:
    uint64_t duration_ns_ = 0;

    Duration(uint64_t duration_ns);
};

auto operator==(const Duration& lhs, const Duration& rhs) -> bool;
auto operator!=(const Duration& lhs, const Duration& rhs) -> bool;
auto operator<(const Duration& lhs, const Duration& rhs) -> bool;
auto operator>(const Duration& lhs, const Duration& rhs) -> bool;
auto operator<=(const Duration& lhs, const Duration& rhs) -> bool;
auto operator>=(const Duration& lhs, const Duration& rhs) -> bool;

} // namespace common::time

#endif //  COMMON_TIME_H
