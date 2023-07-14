#include <Omni.h>
#include <gtest/gtest.h>

#include <array>

using namespace rct;

TEST(OMNI_4, SIZE) {
  EXPECT_EQ(4, Omni<4>::size());
}

TEST(OMNI_4, MOVE) {
  Omni<4> omni{[](std::array<float, 4> pow) {
    for(auto e: pow) EXPECT_FLOAT_EQ(0.0, e);
  }};
  omni.move(Velocity{});
}

TEST(OMNI_4, MOVE_WITH_VEL) {
  Omni<4> omni{[](std::array<float, 4> pow) {
    EXPECT_FLOAT_EQ(cos(0), pow[0]);
    EXPECT_FLOAT_EQ(cos(M_PI / 2), pow[1]);
    EXPECT_FLOAT_EQ(cos(M_PI), pow[2]);
    EXPECT_FLOAT_EQ(cos(3 * M_PI / 2), pow[3]);
  }};
  omni.move(Velocity{1.0});
}

TEST(OMNI_4, MOVE_WITH_ANG) {
  Omni<4> omni{[](std::array<float, 4> pow) {
    EXPECT_FLOAT_EQ(-1.0, pow[0]);
    EXPECT_FLOAT_EQ(-1.0, pow[1]);
    EXPECT_FLOAT_EQ(-1.0, pow[2]);
    EXPECT_FLOAT_EQ(-1.0, pow[3]);
  }};
  omni.move(Velocity{0.0, 0.0, -1.0});
}
