#include <Pwm.h>
#include <gtest/gtest.h>

using namespace rct;

TEST(PWM, C_TOR) {
  Pwm pwm{};
  EXPECT_FLOAT_EQ(0.0, pwm[0]);
  EXPECT_FLOAT_EQ(0.0, pwm[1]);
}

TEST(PWM, C_TOR_WITH_POSITIVE_VALUE) {
  Pwm pwm{0.5};
  EXPECT_FLOAT_EQ(0.5, pwm[0]);
  EXPECT_FLOAT_EQ(0.0, pwm[1]);
}

TEST(PWM, C_TOR_WITH_NEGATIVE_VALUE) {
  Pwm pwm{-0.5};
  EXPECT_FLOAT_EQ(0.0, pwm[0]);
  EXPECT_FLOAT_EQ(0.5, pwm[1]);
}

TEST(PWM, SET_POSITIVE) {
  Pwm pwm{};
  pwm.set(1.0);
  EXPECT_FLOAT_EQ(1.0, pwm[0]);
  EXPECT_FLOAT_EQ(0.0, pwm[1]);
}

TEST(PWM, SET_NEGATIVE) {
  Pwm pwm{};
  pwm.set(-1.0);
  EXPECT_FLOAT_EQ(0.0, pwm[0]);
  EXPECT_FLOAT_EQ(1.0, pwm[1]);
}

TEST(PWM, ASSIGNMENT_POSITIVE) {
  Pwm pwm{};
  pwm = 0.3;
  EXPECT_FLOAT_EQ(0.3, pwm[0]);
  EXPECT_FLOAT_EQ(0.0, pwm[1]);
}

TEST(PWM, ASSIGNMENT_NEGATIVE) {
  Pwm pwm{};
  pwm = -0.3;
  EXPECT_FLOAT_EQ(0.0, pwm[0]);
  EXPECT_FLOAT_EQ(0.3, pwm[1]);
}
