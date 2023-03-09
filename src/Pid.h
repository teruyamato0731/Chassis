#ifndef CHASSIS_PID_H_
#define CHASSIS_PID_H_
/// @file
/// @brief PID制御を行う Pid クラスを提供する。
/// @copyright Copyright (c) 2022 Yoshikawa Teru
/// @license This project is released under the MIT License, see [LICENSE](https://github.com/teruyamato0731/Chassis/blob/main/LICENSE)
#include <chrono>

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

/// @brief T型がPID制御可能な型であるかを判定する。
/// @tparam T 判定を行う型
template<class T>
class is_pidable {
  template<class U, class = U>
  struct is_pidable_helper : std::false_type {};
  template<class U>
  struct is_pidable_helper<U, decltype(std::declval<U&>() = std::declval<U>() + std::declval<U>(),
                                       std::declval<U&>() = std::declval<U>() - std::declval<U>(),
                                       std::declval<U&>() = std::declval<U>() * std::declval<float>(),
                                       std::declval<U&>() = std::declval<U>() / std::declval<float>(), U{})>
      : std::true_type {};
 public:
  /// @brief T型同士の加減算とfloat型との乗除が定義されていて、デフォルト初期化が可能であればtrue, そうでなければfalse。
  static constexpr bool value = is_pidable_helper<T>::value;
};

/// @brief T型がPID制御可能な型であるかを判定する。
/// T型同士の加減算とfloat型との乗除が定義されていればtrue, そうでなければfalse。
/// @tparam T 判定を行う型
template<class T>
constexpr bool is_pidable_v = is_pidable<T>::value;

/// @brief T型のPID制御を行うクラス。
/// @tparam T PID制御可能な型であること。(T型同士の加減算とfloat型との乗除が定義されていること。)is_pidableで判定可能。
template<class T>
struct Pid {
  static_assert(is_pidable_v<T>, "T型がPID制御に対応していません。");

  /// @brief コンストラクタ。ゲインをセットする。
  /// @param pid_gain PID制御のゲイン
  Pid(const PidGain& pid_gain, const T& init = T{}) noexcept : pid_gain_{pid_gain}, pre_{init} {}

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
    pre_ = now;
    return proportional * pid_gain_.kp + integral_ * pid_gain_.ki + differential * pid_gain_.kd;
  }

  /// @brief I値をリセットする。
  void refresh(const T& init = T{}) noexcept {
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
  T integral_{};
  T pre_;
};

/// @}  pid

/// @}  utility

}  // namespace rct

#endif  // CHASSIS_PID_H_
