#include <../snippets/Motor.h>
#include <Odom.h>
#include <mbed.h>

#include <array>
#include <functional>

using namespace rct;

Timer timer;
Odom<3> odom{};

int main() {
  timer.start();
  while(1) {
    // 時間を取得
    auto now = timer.elapsed_time();
    static auto pre = now;
    auto delta = pre - now;

    // エンコーダの値を引数に渡す
    odom.integrate({0, 0, 0});
    auto pos = odom.get();
    auto vel = pos / delta;

    pre = now;
  }
}
