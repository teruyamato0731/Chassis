#ifndef RCT_CHASSIS_PID_H_
#define RCT_CHASSIS_PID_H_
/// @file
/// @brief 足回りの速度のPID制御を行うChassisPidを提供する。
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

/// @brief 足回りの速度のPID制御を行う。
/// @tparam T
template<class T>
struct ChassisPid {
  /// @brief コンストラクタ。T型をfで初期化し、変位と速度のPIDゲインをセットする。
  /// @tparam F 関数型。T型に与えるcallback関数の型。
  /// @param f callback関数。
  /// @param vel_gain 手動速度制御のPIDゲイン
  template<class F>
  ChassisPid(F&& f, const PidGain& vel_gain) : t_{std::forward<F>(f)}, vel_pid_{vel_gain} {}

  /// @copydoc Chassis::pid_move
  void pid_move(const Velocity& tag_vel, const Velocity& now_vel, const std::chrono::microseconds& delta_time) {
    const auto out_vel = vel_pid_.calc(tag_vel, now_vel, delta_time);
    t_.move(out_vel);
  }

 private:
  T t_;
  Pid<Velocity> vel_pid_;
};

/// @}

}  // namespace rct

#endif  // RCT_CHASSIS_PID_H_
