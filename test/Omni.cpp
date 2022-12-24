#include <Omni.h>
#include <gtest/gtest.h>

using namespace rct;

TEST(OMNI, TYPE) {
  EXPECT_EQ(3, Omni<3>::size());
}

TEST(OMNI, MOVE) {
  Omni<3> omni{[](const float(&pow)[3]) {
    for(auto e: pow) EXPECT_EQ(0, e);
  }};
  omni.move(Velocity{});
}
