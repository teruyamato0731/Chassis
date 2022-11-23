#ifndef CHASSIS_STEER_DRIVE_H_
#define CHASSIS_STEER_DRIVE_H_
/// @file
/// @brief N輪独立ステアリングの制御を行う SteerDrive クラスを提供する。
/// @copyright Copyright (c) 2022 Yoshikawa Teru
/// @license [This project is released under the MIT License.](https://github.com/teruyamato0731/Chassis/blob/main/LICENSE)
#include <cmath>
#include <complex>
#include <functional>

namespace rct {

/// @addtogroup frame
/// @{

/// @brief N輪独立ステアリング駆動機
/// @tparam N ステアリングホイール数。 N > 0であること。
template<int N>
struct SteerDrive {
  static_assert(N > 0);

  /// @brief コンストラクタ。callback関数をセットする。
  /// @tparam F 関数型。引数に const std::complex<float> (&)[N] を受け取り、返り値が void であること。
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
  void move(const Velocity& vel, float offset) {
    std::complex<float> vels[N];
    const std::complex<float> ang = std::polar<float>(vel.ang, 0);
    for(int i = 0; i < N; ++i) {
      const std::complex<float> vel_fix = std::polar<float>(std::hypot(vel.x, vel.y), -offset - 2 * M_PI / N * i);
      vels[i] = vel_fix - ang;
    }
    f_(vels);
  }
 private:
  std::function<void(const std::complex<float> (&)[N])> f_;
};

/// @}

}  // namespace rct

#endif CHASSIS_STEER_DRIVE_H_
