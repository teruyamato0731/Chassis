#include <Pid.h>
#include <gtest/gtest.h>

#include <type_traits>

using namespace rct;
using namespace std::literals::chrono_literals;

TEST(PID_GAIN, TYPE_TRAIT) {
  EXPECT_TRUE(std::is_trivial<PidGain>::value);
  EXPECT_TRUE(std::is_standard_layout<PidGain>::value);
}

TEST(IS_PIDABLE, ACCEPT_TYPE) {
  EXPECT_TRUE(is_pidable_v<int>);
  EXPECT_TRUE(is_pidable_v<float>);

  struct Hoge {};
  EXPECT_FALSE(is_pidable_v<Hoge>);
}

TEST(PID, TYPE_TRAIT) {
  EXPECT_TRUE(noexcept(Pid<int>{{}}));
  EXPECT_TRUE(noexcept(Pid<float>{{}}));
}

TEST(PID, CALC_ZERO) {
  Pid<float> pid{{}};
  EXPECT_FLOAT_EQ(0.0, pid.calc(1, 0, 1s));
}

TEST(PID, CALC_P) {
  Pid<float> pid{{0.1}};
  EXPECT_FLOAT_EQ(0.1, pid.calc(1, 0, 1s));
}

TEST(PID, CALC_I) {
  Pid<float> pid{{0.1, 0.1}};
  EXPECT_FLOAT_EQ(0.2, pid.calc(1, 0, 1s));
  EXPECT_FLOAT_EQ(0.3, pid.calc(1, 0, 1s));
}

TEST(PID, SET_PID_GAIN) {
  Pid<float> pid{{}};
  EXPECT_FLOAT_EQ(0.0, pid.calc(1, 0, 1s));
  pid.set_pid_gain({0.1});
  EXPECT_FLOAT_EQ(0.1, pid.calc(1, 0, 1s));
}

TEST(PID, REFRESH) {
  Pid<float> pid{{0.1}};
  EXPECT_FLOAT_EQ(0.1, pid.calc(1, 0, 1s));
  pid.refresh();
  EXPECT_FLOAT_EQ(0.1, pid.calc(1, 0, 1s));
}
