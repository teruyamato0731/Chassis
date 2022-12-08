/// @file
/// @brief 4輪独立ステアリングの制御例
#include <../snippets/Motor.h>
#include <SteerDrive.h>
#include <mbed.h>

#include <array>

using namespace rct;

Motor motors[4] = {{D8, D9}, {D10, D11}, {D12, D13}, {D14, D15}};
PwmOut servo[4] = {D4, D5, D6, D7};
/// [construct]
SteerDrive<4> steer{[](const std::complex<float> (&cmp)[4]) {
  for(int i = 0; i < 4; ++i) {
    motors[i] = abs(cmp[i]);
    servo[i] = arg(cmp[i]);
  }
}};
/// [construct]

int main() {
  // put your setup code here, to run once:
  while(1) {
    // put your main code here, to run repeatedly:
    /// [move]
    Velocity vel = {0, 0.5, 0};
    steer.move(vel);
    /// [move]
  }
}
