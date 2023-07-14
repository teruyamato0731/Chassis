#ifndef CHASSIS_ODOM_H_
#define CHASSIS_ODOM_H_
/// @file
/// @brief オドメトリを行う Odom クラスを提供する。
/// @copyright Copyright (c) 2022-2023 Yoshikawa Teru
/// @license This project is released under the MIT License, see [LICENSE](https://github.com/teruyamato0731/Chassis/blob/main/LICENSE).
#include <CoordinateUnit.h>

#include <cmath>
#include <utility>

namespace rct {

/// @brief 自己位置推定を行う。
/// @defgroup localization localization
/// @{

/// @brief N個のエンコーダでオドメトリを行うクラス。
/// @tparam N エンコーダ数。 N > 0 であること。
template<int N>
struct Odom {
  static_assert(N > 0, "template parameter N must be greater than 0");

  /// @brief コンストラクタ。現在位置を初期化する。
  /// @param pos 現在位置
  Odom(const Coordinate& pos = {}) : pos_{pos} {}
  /// @brief エンコーダ数を返す。
  /// @return Odom クラスの templateパラメータである N 定数を返す。
  static constexpr int size() noexcept {
    return N;
  }

  /// @brief エンコーダの変位の変化量を積分し、自己位置を計算する。
  /// @param dif_val 変位の変化量
  void integrate(const int (&dif_val)[N]) {
    constexpr float pi_N = M_PI / N;
    const float tmp_rad = pos_.ang_rad;
    for(int i = 0; i < N; ++i) {
      pos_.x_milli += dif_val[i] * cos((2 * i + 1) * pi_N + tmp_rad);
      pos_.y_milli += dif_val[i] * sin((2 * i + 1) * pi_N + tmp_rad);
      pos_.ang_rad += dif_val[i];
    }
  }

  /// @{
  /// @brief 推定された自己位置を返す。
  /// @return 左辺値の文脈ではCoordinateのconst参照を返し、右辺値の文脈ではCoordinateをコピーして返す。
  const Coordinate& get() const& noexcept {
    return pos_;
  }
  Coordinate get() && noexcept {
    return std::move(pos_);
  }
  /// @}

  /// @brief 自己位置を更新する。
  /// @param pos セットする自己位置。
  void set(const Coordinate& pos) noexcept {
    pos_ = pos;
  }

 private:
  Coordinate pos_;
};

/// @}

}  // namespace rct

#endif  // CHASSIS_ODOM_H_
