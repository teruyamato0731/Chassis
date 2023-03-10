#include <CoordinateUnit.h>
#include <gtest/gtest.h>

#include <type_traits>

using namespace rct;
using namespace std::literals::chrono_literals;

TEST(COORDINATE_UNIT, TYPE_TRAIT) {
  EXPECT_TRUE(std::is_trivial<Coordinate>::value);
  EXPECT_TRUE(std::is_trivial<Velocity>::value);
  EXPECT_TRUE(std::is_standard_layout<Coordinate>::value);
  EXPECT_TRUE(std::is_standard_layout<Velocity>::value);
}

TEST(COORDINATE_UNIT, DIMENSION) {
  EXPECT_EQ(0, Coordinate::dimension());
  EXPECT_EQ(-1, Velocity::dimension());
}

TEST(COORDINATE_UNIT, COMPARE_EQ) {
  {
    Coordinate p1{0.5, 100, 3.14};
    Coordinate p2{0.5, 100, 3.14};
    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 != p2);
  }
  {
    Coordinate p1{};
    Coordinate p2{0.5, 100, 3.14};
    EXPECT_FALSE(p1 == p2);
    EXPECT_TRUE(p1 != p2);
  }
}

TEST(COORDINATE_UNIT, ADD) {
  Coordinate p1{0.5, 100, 3.14};
  Coordinate p2{0.5, 100, 3.14};
  Coordinate expect{1.0, 200, 6.28};
  EXPECT_EQ(expect, p1 + p2);
}

TEST(COORDINATE_UNIT, SUB) {
  Coordinate p1{0.5, 100, 3.14};
  Coordinate p2{0.5, 100, 3.14};
  EXPECT_EQ(Coordinate{}, p1 - p2);
}

TEST(COORDINATE_UNIT, MUL) {
  Coordinate p1{0.5, 100, 3.14};
  Coordinate expect1{-1.0, -200, -6.28};
  EXPECT_EQ(expect1, p1 * -2);

  Coordinate p2{0.5, 100, 3.14};
  Coordinate expect2{1.5, 300, 9.42};
  EXPECT_EQ(expect2, 3 * p2);
}

TEST(COORDINATE_UNIT, MUL_DURATION) {
  Velocity p1{0.5, 100, 3.14};
  Coordinate expect1{0.05, 10, 0.314};
  EXPECT_EQ(expect1, p1 * 100ms);

  Velocity p2{0.5, 100, 3.141592};
  Coordinate expect2{5, 1000, 31.41592};
  EXPECT_EQ(expect2, 10s * p2);
}

TEST(COORDINATE_UNIT, DIV_DURATION) {
  Coordinate p1{0.5, 100, 3.14};
  Velocity expect1{0.05, 10, 0.314};
  EXPECT_EQ(expect1, p1 / 10s);

  Coordinate p2{0.5, 100, 3.141592};
  Velocity expect2{500, 1e5, 3.141592e3};
  EXPECT_EQ(expect2, p2 / 1ms);
}

TEST(COORDINATE_UNIT, DISTANCE) {
  {
    Coordinate p1{0.5, 100, 0.0};
    Coordinate p2{0.5, 100, 1.57};
    EXPECT_FLOAT_EQ(0.0, distance(p1, p2));
  }
  {
    Coordinate p1{};
    Coordinate p2{10, 10, 0};
    EXPECT_FLOAT_EQ(14.14213562, distance(p1, p2));
  }
}
