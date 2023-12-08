#ifndef RCT_CHASSIS_H_
#define RCT_CHASSIS_H_
/// @file
/// @brief 足回りの自動制御を行う Chassis クラスを提供する。
/// @copyright Copyright (c) 2022-2023 Yoshikawa Teru
/// @license This project is released under the MIT License, see [LICENSE](https://github.com/teruyamato0731/Chassis/blob/main/LICENSE).
#include <CoordinateUnit.h>
#include <Pid.h>

#include <chrono>
#include <cmath>
#include <cstdint>
#include <utility>

/// @brief robot control library
namespace rct {

/// @brief 自動制御を行う。
/// @defgroup chassis chassis
/// @{

/// @brief 足回りの自動制御を行うクラス。
/// @tparam T 自動制御を行うクラス。
template<class T>
struct Chassis {
  /// @brief コンストラクタ。T型をfで初期化し、変位と速度のPIDゲインをセットする。
  /// @tparam F 関数型。T型に与えるcallback関数の型。
  /// @param f callback関数。
  /// @param vel_gain 手動速度制御のPIDゲイン
  /// @param pos_gain 自動制御のPIDゲイン
  template<class F>
  Chassis(F&& f, const PidGain& vel_gain, const PidGain& pos_gain)
      : t_{std::forward<F>(f)}, vel_pid_{vel_gain}, pos_pid_{pos_gain} {}

  /// @brief 手動操縦用。速度のPID制御を行い、出力をT型のcalcに渡す
  /// @param tag_vel 目標速度
  /// @param now_vel 現在速度
  /// @param delta_time 前回呼び出しからの経過時間
  /// @param offset_rad 姿勢角
  void pid_move(const Velocity& tag_vel, const Velocity& now_vel, const std::chrono::microseconds& delta_time,
                const float offset_rad = {}) {
    const auto out_vel = vel_pid_.calc(tag_vel, now_vel, delta_time);
    t_.move(out_vel, offset_rad);
  }
  /// @brief 自動制御用。変位のPID制御を行い、出力をT型のcalcに渡す。
  /// @param dst 目標座標
  /// @param pos 現在座標
  /// @param delta_time 前回呼び出しからの経過時間
  void auto_move(const Coordinate& dst, const Coordinate& pos, const std::chrono::microseconds& delta_time) {
    const auto out_vel = pos_pid_.calc(dst, pos, delta_time) / std::chrono::seconds{1};
    t_.move(out_vel, pos.ang_rad);
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
  Pid<Velocity> vel_pid_;
  Pid<Coordinate> pos_pid_;
};

/// @}

}  // namespace rct

#endif  // RCT_CHASSIS_H_
