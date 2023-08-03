#pragma once

#include "../common/timeutils.h"
#include <cstdint>

namespace engine {

class RateCounter final {
public:
    void inc();
    auto hertz() const -> float;

private:
    common::time::Instant start_time_ = common::time::Instant::now();
    uint32_t counter_{0};
    float prev_hertz_{0};
    float cur_hertz_{0};
};

} // namespace engine
