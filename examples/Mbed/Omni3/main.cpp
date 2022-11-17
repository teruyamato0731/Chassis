/// @file
/// @brief Omniの使用例 Mbed用

#include <Omni.h>
#include <mbed.h>

#include <array>

#include "Motor.h"

using namespace rct;

Motor motors[3] = {{D10, D11}, {D12, D13}, {D12, D13}};
Omni<3> omni{[](const float (&pwm)[3]) {
  for(int i = 0; i < 3; ++i) {
    motors[i] = pwm[i];
  }
}};

int main() {
  // put your setup code here, to run once:
  while(1) {
    // put your main code here, to run repeatedly:
    Velocity vel = {0, 0.5, 0};
    omni.move(vel);
  }
}
