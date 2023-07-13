#ifndef CHASSIS_STEER_DRIVE_H_
#define CHASSIS_STEER_DRIVE_H_
/// @file
/// @brief N輪独立ステアリングの制御を行う SteerDrive クラスを提供する。
/// @copyright Copyright (c) 2022-2023 Yoshikawa Teru
/// @license This project is released under the MIT License, see [LICENSE](https://github.com/teruyamato0731/Chassis/blob/main/LICENSE).
#include <CoordinateUnit.h>

#include <array>
#include <cmath>
#include <complex>
#include <functional>
#include <utility>

namespace rct {

/// @addtogroup frame
/// @{

/// @brief N輪独立ステアリング駆動機
/// @tparam N ステアリングホイール数。 N > 0であること。
template<int N>
struct SteerDrive {
  static_assert(N > 0, "template parameter N must be greater than 0");

  /// @brief コンストラクタ。callback関数をセットする。
  /// @tparam F 関数型。引数に std::array<std::complex<float>, N> を受け取り、返り値が void であること。
  /// @param f callback関数
  template<class F>
  SteerDrive(F&& f) : f_{std::forward<F>(f)} {}

  /// @brief モータ数を返す。
  /// @return SteerDrive クラスの templateパラメータである N 定数を返す。
  static constexpr int size() noexcept {
    return N;
  }

  /// @brief モータへのPWM出力を計算する。その後callback関数にPWM出力を渡す。
  /// @param vel 移動速度
  /// @param offset_rad 姿勢角
  void move(const Velocity& vel, float offset_rad = 0.0) {
    std::array<std::complex<float>, N> vels;
    const std::complex<float> rotate = std::polar<float>(vel.ang_rad, 0);
    for(int i = 0; i < N; ++i) {
      float ang = -offset_rad - M_PI / N * (2 * i + 1) + std::atan2(vel.y_milli, vel.x_milli);
      const std::complex<float> vel_fix = std::polar<float>(std::hypot(vel.x_milli, vel.y_milli), ang);
      vels[i] = vel_fix + rotate;
    }
    f_(std::move(vels));
  }
 private:
  std::function<void(std::array<std::complex<float>, N>)> f_;
};

/// @}

}  // namespace rct

#endif  // CHASSIS_STEER_DRIVE_H_
