#ifndef CHASSIS_PID_H_
#define CHASSIS_PID_H_
/// @file
/// @brief PID制御を行う Pid クラスを提供する。
/// @copyright Copyright (c) 2022-2023 Yoshikawa Teru
/// @license This project is released under the MIT License, see [LICENSE](https://github.com/teruyamato0731/Chassis/blob/main/LICENSE).
#include <chrono>
#include <type_traits>

namespace rct {

/// @brief 有用な機能群を提供する。
/// @defgroup utility utility
/// @{

/// @brief PID制御を提供する。
/// @defgroup pid pid
/// @{

/// @brief PID制御のゲイン
struct PidGain {
  float kp;  ///< 比例ゲイン
  float ki;  ///< 積分ゲイン
  float kd;  ///< 微分ゲイン
};

/// @brief T型のPID制御を行うクラス。
/// @tparam T PID制御可能な型であること。(T型同士の加減算とfloat型との乗除が定義されていること。)is_pidableで判定可能。
template<class T>
struct Pid {
  static_assert(std::is_floating_point_v<T>, "template parameter T must be floating point.");

  /// @brief コンストラクタ。ゲインをセットする。
  /// @param pid_gain PID制御のゲイン
  /// @param init 初期値
  Pid(const PidGain& pid_gain, const T& init = NAN) noexcept : pid_gain_{pid_gain}, pre_{init} {}

  /// @brief 目標値、現在値、経過時間からPID制御の計算を行う。
  /// @param dst 目標値
  /// @param now 現在値
  /// @param delta_time 前回呼び出しからの経過時間
  /// @return T型 PIDの結果を返す。
  T calc(const T& dst, const T& now, const std::chrono::microseconds& delta_time) {
    const float sec = std::chrono::duration<float>{delta_time}.count();
    const T proportional = dst - now;
    integral_ += proportional * sec;
    const T differential = now - pre_ / sec;
    if constexpr(std::is_floating_point_v<T>) {
      if(std::isnan(differential)) differential = T{};
    }
    pre_ = now;
    return proportional * pid_gain_.kp + integral_ * pid_gain_.ki + differential * pid_gain_.kd;
  }

  /// @brief I値をリセットする。
  void refresh(const T& init = NAN) noexcept(T{}) {
    integral_ = T{};
    pre_ = init;
  }

  /// @brief ゲインをセットし、refreshを呼び出す。
  /// @param pid_gain PID制御のゲイン
  void set_pid_gain(const PidGain& pid_gain) noexcept {
    pid_gain_ = pid_gain;
    refresh();
  }

 private:
  PidGain pid_gain_;
  T pre_;
  T integral_{};
};

/// @}  pid

/// @}  utility

}  // namespace rct

#endif  // CHASSIS_PID_H_
