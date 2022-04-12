#include "common/strutils.h"
#include <gtest/gtest.h>

using namespace common::str;

TEST(Format, FormatShouldWork) {
    auto result = format("%s %s", "hello,", "world");
    EXPECT_EQ(result, "hello, world");
}
