#include "common/Result.h"
#include <gtest/gtest.h>

using namespace common::result;

TEST(Result, SuccessResultCanBeConstructed) {
    auto result1 = make_success_result(1);
    EXPECT_EQ(result1.is_ok(), true);
    EXPECT_EQ(result1.is_error(), false);
    EXPECT_EQ(result1.value(), 1);

    auto result2 = make_success_result("one two three");
    ASSERT_STREQ(result2.value(), "one two three");
}

TEST(Result, SuccessResultCanBeReleased) {
    auto result1 = make_success_result(123);
    auto released_value = result1.release_value();
    EXPECT_EQ(released_value, 123);
}
