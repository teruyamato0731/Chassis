#ifndef RCT_CHASSIS_AUTO_H_
#define RCT_CHASSIS_AUTO_H_
/// @file
/// @brief 足回りの位置のPID制御を行うChassisAutoを提供する。
/// @copyright Copyright (c) 2022-2023 Yoshikawa Teru
/// @license This project is released under the MIT License, see [LICENSE](https://github.com/teruyamato0731/Chassis/blob/main/LICENSE).
#include <CoordinateUnit.h>
#include <Pid.h>

#include <chrono>
#include <cmath>
#include <cstdint>
#include <utility>

namespace rct {

/// @addtogroup chassis
/// @{

// TODO CRTP
/// @brief 足回りの位置のPID制御を行う。
/// @tparam T
template<class T>
struct ChassisAuto {
  /// @brief コンストラクタ。T型をfで初期化し、変位と速度のPIDゲインをセットする。
  /// @tparam F 関数型。T型に与えるcallback関数の型。
  /// @param f callback関数。
  /// @param pos_gain 自動制御のPIDゲイン
  template<class F>
  ChassisAuto(F&& f, const PidGain& pos_gain) : t_{std::forward<F>(f)}, pos_pid_{pos_gain} {}

  /// @copydoc Chassis::auto_move
  void auto_move(const Coordinate& dst, const Coordinate& pos, const std::chrono::microseconds& delta_time) {
    const auto out_vel = pos_pid_.calc(dst, pos, delta_time) / std::chrono::seconds{1};
    t_.move(out_vel);
  }

  // TODO
  auto move(const Velocity& vel, const float offset_rad = {}) {
    t_.move(vel, offset_rad);
  }

  // TODO
  auto refresh() {
    return vel_pid_.refresh();
  }

 private:
  T t_;
  Pid<Coordinate> pos_pid_;
};

/// @}

}  // namespace rct

#endif  // RCT_CHASSIS_AUTO_H_
