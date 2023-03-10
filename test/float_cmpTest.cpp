#include <gtest/gtest.h>

#include "bits/float_cmp.h"

using namespace rct;

TEST(FLOAT_CMP, LESS) {
  EXPECT_EQ(-1, float_cmp(0.0, 1.0));
  EXPECT_EQ(-1, float_cmp(1.0, 100));
  EXPECT_EQ(-1, float_cmp(-1e-6, -2e-6));
}

TEST(FLOAT_CMP, EQUAL) {
  EXPECT_EQ(0, float_cmp(0.0, 0.0));
  EXPECT_EQ(0, float_cmp(1e3, 1e3));
  EXPECT_EQ(0, float_cmp(1e6, 1e6));
}

TEST(FLOAT_CMP, GREATER) {
  EXPECT_EQ(1, float_cmp(1.0, 0.0));
  EXPECT_EQ(1, float_cmp(1e3, -1e3));
  EXPECT_EQ(1, float_cmp(1.3e6, 1e6));
}
