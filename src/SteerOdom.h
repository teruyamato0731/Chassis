#ifndef RCT_STEER_ODOM_H_
#define RCT_STEER_ODOM_H_

#include <CoordinateUnit.h>

#include <complex>

namespace rct {

/// @brief 自己位置推定を行う。
/// @defgroup localization localization
/// @{


/// @brief N輪独立ステアリングでオドメトリを行うクラス。
/// @tparam N エンコーダ数。 N > 0 であること。
template<int N>
struct SteerOdom {
  static_assert(N > 0, "template parameter N must be greater than 0");

  /// @brief エンコーダ数を返す。
  /// @return Odom クラスの templateパラメータである N 定数を返す。
  static constexpr int size() noexcept {
    return N;
  }

  // TODO grid point
  /// @brief エンコーダの変位の変化量を積分し、自己位置を計算する。
  /// @param dif_val 変位ベクトル
  void integrate(std::complex<float> (&dif_val)[N]) {
    constexpr float pi_N = M_PI / N;
    for(int i = 0; i < N; ++i) {
      auto rotated = dif_val[i] * std::polar<float>(1, (2 * i) * pi_N);
      pos_.x_milli += rotated.real();
      pos_.y_milli += rotated.imag();
      pos_.ang_rad += dif_val[i].real();
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


#endif  // RCT_STEER_ODOM_H_
