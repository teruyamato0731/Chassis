#include <Omni.h>
#include <gtest/gtest.h>

using namespace rct;

TEST(OMNI_3, SIZE) {
  EXPECT_FLOAT_EQ(3, Omni<3>::size());
}

TEST(OMNI_3, MOVE) {
  Omni<3> omni{[](const float(&pow)[3]) {
    for(auto e: pow) EXPECT_FLOAT_EQ(0.0, e);
  }};
  omni.move(Velocity{});
}

TEST(OMNI_3, MOVE_WITH_VEL) {
  Omni<3> omni{[](const float(&pow)[3]) {
    EXPECT_FLOAT_EQ(cos(0), pow[0]);
    EXPECT_FLOAT_EQ(cos(2 * M_PI / 3), pow[1]);
    EXPECT_FLOAT_EQ(cos(-2 * M_PI / 3), pow[2]);
  }};
  omni.move(Velocity{1.0});
}

TEST(OMNI_3, MOVE_WITH_ANG) {
  Omni<3> omni{[](const float(&pow)[3]) {
    EXPECT_FLOAT_EQ(1.0, pow[0]);
    EXPECT_FLOAT_EQ(1.0, pow[1]);
    EXPECT_FLOAT_EQ(1.0, pow[2]);
  }};
  omni.move(Velocity{0.0, 0.0, 1.0});
}
