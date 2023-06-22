/// @file
/// @brief 3輪オムニ制御例
#include <../snippets/Motor.h>
#include <Omni.h>
#include <mbed.h>

#include <array>

using namespace rct;

Motor motors[3] = {{D10, D11}, {D12, D13}, {D12, D13}};
/// [construct]
Omni<3> omni{[](std::array<float, 3> pwm) {
  for(int i = 0; i < 3; ++i) {
    motors[i] = pwm[i];
  }
}};
/// [construct]

int main() {
  // put your setup code here, to run once:
  while(1) {
    // put your main code here, to run repeatedly:
    /// [move]
    Velocity vel = {0, 0.5, 0};
    omni.move(vel);
    /// [move]
  }
}
