/// @file
/// @brief 自動制御
#include <../snippets/Motor.h>
#include <ChassisAuto.h>
#include <Odom.h>
#include <Omni.h>
#include <PollingTimer.h>
#include <mbed.h>

#include <array>
#include <functional>

using namespace rct;

Timer timer;
Odom<3> odom{};
Motor motors[3] = {{D10, D11}, {D12, D13}, {D12, D13}};
ChassisAuto<Omni<3>> chassis{[](const float (&pwm)[3]) {
                               for(int i = 0; i < 3; ++i) {
                                 motors[i] = pwm[i];
                               }
                             },
                             PidGain{0.1}};

bool check_reached(const Coordinate& dst, const Coordinate& pos);

int main() {
  timer.start();
  while(1) {
    // エンコーダ角変位の変化量を引数に渡す
    odom.integrate({0, 0, 0});
    auto now = timer.elapsed_time();
    static auto pre = now;
    auto delta = pre - now;

    Coordinate dst = {0, 1000, 0.0};
    Coordinate pos = odom.get();
    chassis.auto_move(dst, pos, delta);
    check_reached(dst, pos);

    pre = now;
  }
}


/// @brief hoge
/// @param dst hoge
/// @param pos hoge
/// @return hoge
bool check_reached(const Coordinate& dst, const Coordinate& pos) {
  if(static PollingTimer wait; wait(1s)) {
    return true;
  } else {
    if(distance(dst, pos) > 100) wait.reset();
    return false;
  }
}
