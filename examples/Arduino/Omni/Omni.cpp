/// @file
/// @brief Omniの使用例 Arduino用

#include <../snippets/Motor.h>
#include <Arduino.h>
#include <Omni.h>

Motor motors[3] = {{D10, D11}, {D12, D13}, {D12, D13}};
Omni<3> omni{[](std::array<float, 3> pwm) {
  for(int i = 0; i < 3; ++i) {
    motors[i] = pwm[i];
  }
}};

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
  Velocity vel = {0, 0.5, 0};
  omni.move(vel);
}

int main() {
  setup();
  while(1) {
    loop();
  }
}
