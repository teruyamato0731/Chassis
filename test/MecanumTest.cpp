#include <Mecanum.h>
#include <gtest/gtest.h>

using namespace rct;

TEST(MECANUM, SIZE) {
  EXPECT_EQ(4, Mecanum::size());
}

TEST(MECANUM, MOVE) {
  Mecanum omni{[](const float(&pow)[4]) {
    for(auto e: pow) EXPECT_FLOAT_EQ(0.0, e);
  }};
  omni.move(Velocity{});
}

TEST(MECANUM, MOVE_WITH_VEL) {
  Mecanum omni{[](const float(&pow)[4]) {
    EXPECT_FLOAT_EQ(0.70710677, pow[0]);
    EXPECT_FLOAT_EQ(0.70710677, pow[1]);
    EXPECT_FLOAT_EQ(0.70710677, pow[2]);
    EXPECT_FLOAT_EQ(0.70710677, pow[3]);
  }};
  omni.move(Velocity{1.0});
}

TEST(MECANUM, MOVE_WITH_ANG) {
  Mecanum omni{[](const float(&pow)[4]) {
    EXPECT_FLOAT_EQ(1.0, pow[0]);
    EXPECT_FLOAT_EQ(1.0, pow[1]);
    EXPECT_FLOAT_EQ(1.0, pow[2]);
    EXPECT_FLOAT_EQ(1.0, pow[3]);
  }};
  omni.move(Velocity{0.0, 0.0, 1.0});
}
