#include <Odom.h>
#include <gtest/gtest.h>

using namespace rct;

TEST(ODOM, SIZE) {
  EXPECT_EQ(3, Odom<3>::size());
  EXPECT_EQ(4, Odom<4>::size());
}

TEST(ODOM, C_TOR) {
  {
    Odom<3> odom{};
    EXPECT_EQ(Coordinate{}, odom.get());
  }
  {
    Coordinate p1{1000, 500, 1.57};
    Odom<3> odom{p1};
    EXPECT_EQ(p1, odom.get());
  }
  {
    Coordinate p1{1000, 500, 1.57};
    EXPECT_EQ(p1, Odom<4>{p1}.get());
    EXPECT_EQ(Coordinate{}, Odom<4>{}.get());
  }
}

TEST(ODOM, SET) {
  Odom<4> odom{};
  Coordinate p1{1000, 500, 1.57};
  odom.set(p1);
  EXPECT_EQ(p1, odom.get());
}

TEST(ODOM, INTEGRATE_3_AHEAD) {
  Odom<3> odom{};
  odom.integrate({100, 0, -100});
  Coordinate expect{0, 173.205080757, 0};
  auto actual = odom.get();
  EXPECT_NEAR(expect.x_milli, actual.x_milli, 5e-5);
  EXPECT_NEAR(expect.y_milli, actual.y_milli, 5e-5);
  EXPECT_NEAR(expect.ang_rad, actual.ang_rad, 5e-5);
}

TEST(ODOM, INTEGRATE_3_ROTATE) {
  Odom<3> odom{};
  odom.integrate({100, 100, 100});
  Coordinate expect{0, 0, 300};
  auto actual = odom.get();
  EXPECT_NEAR(expect.x_milli, actual.x_milli, 5e-5);
  EXPECT_NEAR(expect.y_milli, actual.y_milli, 5e-5);
  EXPECT_NEAR(expect.ang_rad, actual.ang_rad, 5e-5);
}

TEST(ODOM, INTEGRATE_4_AHEAD) {
  Odom<4> odom{};
  odom.integrate({100, 100, -100, -100});
  Coordinate expect{0, 282.842712475, 0};
  auto actual = odom.get();
  EXPECT_NEAR(expect.x_milli, actual.x_milli, 5e-5);
  EXPECT_NEAR(expect.y_milli, actual.y_milli, 5e-5);
  EXPECT_NEAR(expect.ang_rad, actual.ang_rad, 5e-5);
}

TEST(ODOM, INTEGRATE_4_ROTATE) {
  Odom<4> odom{};
  odom.integrate({100, 100, 100, 100});
  Coordinate expect{0, 0, 400};
  auto actual = odom.get();
  EXPECT_NEAR(expect.x_milli, actual.x_milli, 5e-5);
  EXPECT_NEAR(expect.y_milli, actual.y_milli, 5e-5);
  EXPECT_NEAR(expect.ang_rad, actual.ang_rad, 5e-5);
}
