#ifndef GAME_TICKLIMITER_H
#define GAME_TICKLIMITER_H

#include "common/timeutils.h"
#include <cstdint>

namespace game {

class TickLimiter final {

public:
    TickLimiter(uint64_t target_ticks_per_second);

    [[nodiscard]] auto should_tick() const -> bool;
    void tick();

private:
    common::time::Duration target_minimum_tick_duration_;
    common::time::Instant last_tick_;
};

} // namespace game

#endif // GAME_TICKLIMITER_H
