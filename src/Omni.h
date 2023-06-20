#ifndef CHASSIS_OMNI_H_
#define CHASSIS_OMNI_H_
/// @file
/// @brief オムニの制御を行う Omni クラスを提供する。
/// @copyright Copyright (c) 2022-2023 Yoshikawa Teru
/// @license This project is released under the MIT License, see [LICENSE](https://github.com/teruyamato0731/Chassis/blob/main/LICENSE).
#include <CoordinateUnit.h>

#include <array>
#include <cmath>
#include <functional>
#include <utility>

namespace rct {

/// @brief 移動速度よりモータを出力に計算する。
/// @details 足回りのモータ出力を計算する。
/// Velocityを与えることにより、コールバック関数を通してモータへの出力をセットする。
/// @defgroup frame frame
/// @{

/// @brief N輪オムニの制御を行うクラス。
/// @tparam N モータ数。 N > 0であること。
template<int N>
struct Omni {
  static_assert(N > 0, "template parameter N must be greater than 0");

  /// @brief コンストラクタ。callback関数をセットする。
  /// @tparam F 関数型。引数に const float (&)[N] を受け取り、返り値が void であること。
  /// @param f callback関数
  template<class F>
  Omni(F&& f) : f_{std::forward<F>(f)} {}

  /// @brief モータ数を返す。
  /// @return Omni クラスの templateパラメータである N 定数を返す。
  static constexpr int size() noexcept {
    return N;
  }

  /// @brief モータへのPWM出力を計算する。その後callback関数にPWM出力を渡す。
  /// @param vel 移動速度
  /// @param offset_rad 姿勢角
  void move(const Velocity& vel, const float offset_rad = 0.0) {
    const float theta_rad = std::atan2(vel.y_milli, vel.x_milli);
    const float run_power = std::hypot(vel.x_milli, vel.y_milli);
    std::array<float, N> pwms;
    for(int i = 0; i < N; ++i) {
      constexpr auto k = 2 * M_PI / N;
      const auto pwm = run_power * std::cos(i * k + theta_rad + offset_rad) + vel.ang_rad;
      pwms[i] = pwm;
    }
    f_(std::move(pwms));
  }

 private:
  std::function<void(std::array<float, N>)> f_;
};

/// @}

}  // namespace rct

#endif  // CHASSIS_OMNI_H_
