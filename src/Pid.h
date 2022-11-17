#ifndef CHASSIS_PID_H_
#define CHASSIS_PID_H_
/// @file
/// @brief PID制御を行う Pid クラスを提供する。
#include <chrono>
#include <optional>

namespace rct {

/// @brief 有用な機能群を提供する。
/// @defgroup utility
/// @{

/// @brief PID制御のゲイン
struct PidGain {
  float kp;
  float ki;
  float kd;
};

// @TODO Pidable
// @TODO static_assert();

/// @brief T型のPID制御を行うクラス。
/// @tparam T T型同士の加減算とfloat型との乗除が定義されていること。
template<class T, decltype(std::declval<T&>() = std::declval<T>() + std::declval<T>(),
                           std::declval<T&>() = std::declval<T>() - std::declval<T>(),
                           std::declval<T&>() = std::declval<T>() * std::declval<float>(),
                           std::declval<T&>() = std::declval<T>() / std::declval<float>(), T{}, nullptr) = nullptr>
struct Pid {
  /// @brief コンストラクタ。ゲインをセットする。
  /// @param pid_gain PID制御のゲイン
  Pid(const PidGain& pid_gain) noexcept : pid_gain_{pid_gain} {}

  /// @brief 目標値、現在値、経過時間からPID制御の計算を行う。
  /// @param dst 目標値
  /// @param now 現在値
  /// @param delta_time 前回呼び出しからの経過時間
  /// @return PIDの結果
  T calc(const T& dst, const T& now, const std::chrono::microseconds& delta_time) {
    const float sec = std::chrono::duration<float>{delta_time}.count();
    const T proportional = dst - now;
    integral_ += proportional * sec;
    const T differential = pre_ ? (now - *pre_) / sec : T{};
    pre_ = now;
    return proportional * pid_gain_.kp + integral_ * pid_gain_.ki + differential * pid_gain_.kd;
  }

  /// @brief I値をリセットする。
  void refresh() noexcept {
    integral_ = T{};
    pre_ = std::nullopt;
  }

  /// @brief ゲインをセットし、refreshを呼び出す。
  /// @param pid_gain PID制御のゲイン
  void set_pid_gain(const PidGain& pid_gain) noexcept {
    pid_gain_ = pid_gain;
    refresh();
  }

 private:
  PidGain pid_gain_;
  T integral_{};
  std::optional<T> pre_{};
};

/// @}

}  // namespace rct

#endif  // CHASSIS_PID_H_
