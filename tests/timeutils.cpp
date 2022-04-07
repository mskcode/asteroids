#include "common/timeutils.h"
#include <gtest/gtest.h>

using namespace common::time;

TEST(Instant, NowShouldReturnCurrentTimeInNanoSeconds) {
    auto now = Instant::now().nanosecond_value();
    EXPECT_GT(now, 0);
}
