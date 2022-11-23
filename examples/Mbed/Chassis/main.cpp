#include <../snipets/Motor.h>
#include <Chassis.h>
#include <Odom.h>
#include <Omni.h>
#include <mbed.h>

#include <array>
#include <functional>

using namespace rct;

Timer timer;
Odom<3> odom{};
Motor motors[3] = {{D10, D11}, {D12, D13}, {D12, D13}};
Chassis<Omni<3>> chassis{[](const float (&pwm)[3]) {
                           for(int i = 0; i < 3; ++i) {
                             motors[i] = pwm[i];
                           }
                         },
                         PidGain{0.1}, PidGain{0.1}};

int main() {
  timer.start();
  while(1) {
    // エンコーダの値を引数に渡す
    odom.integrate({0, 0, 0});
    auto now = timer.elapsed_time();
    static auto pre = now;
    auto delta = pre - now;
#if 1
    // ex 1
    Velocity tag_vel = {0, 0.5, 0.05};
    Velocity now_vel = odom.get() / delta;
    chassis.pid_move(tag_vel, now_vel, delta);
#else
    // ex 2
    Coodinate dst = {0, 1000, 0.0};
    Coodinate pos = odom.get();
    chassis.auto_move(dst, pos, delta);
    check_reached(dst, pos);
#endif
    pre = now;
  }
}
