/// @file
/// @brief オドメトリによる自己位置推定
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
    // エンコーダ角変位の変化量を引数に渡す
    odom.integrate({0, 0, 0});

    // 現在座標の取得
    Coordinate pos = odom.get();

    // 前回からの経過時間を取得
    auto now = timer.elapsed_time();
    static decltype(now) pre = {};
    auto delta = pre - now;
    pre = now;

    // 速度の取得
    static Coordinate pre_pos = {};
    Velocity vel = (pos - pre_pos) / delta;
    pre_pos = pos;

    printf("pos{x:%d,y:%d:,ang:%d}", pos.x_milli, pos.y_milli, pos.ang_rad * 180 / M_PI);
    printf("vel{x:%d,y:%d:,ang:%d}", vel.x_milli, vel.y_milli, vel.ang_rad * 180 / M_PI);
  }
}
