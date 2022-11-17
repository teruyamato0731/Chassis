#ifndef CHASSIS_MECANUM_H_
#define CHASSIS_MECANUM_H_
/// @file
/// @brief メカナムの制御を行う Mecanum クラスを提供する。
#include <CoodinateUnit.h>

#include <cmath>
#include <functional>
#include <utility>

namespace rct {

/// @addtogroup frame
/// @{

/// @brief メカナムの制御を行うクラス。
struct Mecanum {
  /// @brief コンストラクタ。callback関数をセットする。
  /// @tparam F 関数型。引数に const float (&)[N] を受け取り、返り値が void であること。
  /// @param f callback関数
  template<class F>
  Mecanum(F&& f) : f_{std::forward<F>(f)} {}

  /// @brief モータ数を返す。
  /// @return Mecanum クラスの templateパラメータである N 定数を返す。
  static constexpr std::size_t size() noexcept {
    return 4;
  }

  /// @brief モータへのPWM出力を計算する。その後callback関数にPWM出力を渡す。
  /// @param vel 移動速度
  /// @param offset_rad 姿勢角
  void move(const Velocity& vel, const float offset_rad = 0.0) {
    const float theta_rad = std::atan2(vel.y_milli, vel.x_milli);
    const float run_power = std::hypot(vel.x_milli, vel.y_milli);
    const float pwmA = run_power * std::cos(M_PI / 4 + theta_rad + offset_rad) + vel.ang_rad;
    const float pwmB = run_power * std::sin(M_PI / 4 + theta_rad + offset_rad) + vel.ang_rad;
    f_({pwmA, pwmB, pwmA, pwmB});
  }

 private:
  std::function<void(const float (&)[4])> f_;
};

/// @}

}  // namespace rct

#endif  // CHASSIS_MECANUM_H_
