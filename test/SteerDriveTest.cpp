#include <SteerDrive.h>
#include <gtest/gtest.h>

using namespace rct;

TEST(STEER_DRIVE, SIZE) {
  EXPECT_EQ(4, SteerDrive<4>::size());
}

TEST(STEER_DRIVE, MOVE) {
  SteerDrive<4> steer{[](const std::complex<float>(&pow)[4]) {
    for(auto e: pow) {
      EXPECT_FLOAT_EQ(0.0, abs(e));
    }
  }};
  steer.move(Velocity{});
}

TEST(STEER_DRIVE, MOVE_WITH_VEL) {
  SteerDrive<4> steer{[](const std::complex<float>(&pow)[4]) {
    EXPECT_FLOAT_EQ(1.0, abs(pow[0]));
    EXPECT_FLOAT_EQ(1.0, abs(pow[1]));
    EXPECT_FLOAT_EQ(1.0, abs(pow[2]));
    EXPECT_FLOAT_EQ(1.0, abs(pow[3]));
    EXPECT_FLOAT_EQ(0.0, arg(pow[0]));
    EXPECT_FLOAT_EQ(-1.5707964, arg(pow[1]));
    EXPECT_FLOAT_EQ(3.1415925, arg(pow[2]));
    EXPECT_FLOAT_EQ(1.5707964, arg(pow[3]));
  }};
  steer.move(Velocity{1.0});
}

TEST(STEER_DRIVE, MOVE_WITH_ANG) {
  SteerDrive<4> steer{[](const std::complex<float>(&pow)[4]) {
    EXPECT_FLOAT_EQ(1.0, abs(pow[0]));
    EXPECT_FLOAT_EQ(1.0, abs(pow[1]));
    EXPECT_FLOAT_EQ(1.0, abs(pow[2]));
    EXPECT_FLOAT_EQ(1.0, abs(pow[3]));
    EXPECT_FLOAT_EQ(-3.1415927, arg(pow[0]));
    EXPECT_FLOAT_EQ(-3.1415927, arg(pow[1]));
    EXPECT_FLOAT_EQ(3.1415927, arg(pow[2]));
    EXPECT_FLOAT_EQ(3.1415927, arg(pow[3]));
  }};
  steer.move(Velocity{0.0, 0.0, 1.0});
}
