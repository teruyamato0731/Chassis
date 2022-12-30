#ifndef CHASSIS_PWM_H_
#define CHASSIS_PWM_H_
/// @file
/// @brief Pwm クラスを提供する。
/// @copyright Copyright (c) 2022 Yoshikawa Teru
/// @license This project is released under the MIT License, see [LICENSE](https://github.com/teruyamato0731/Chassis/blob/main/LICENSE)

namespace rct {

/// @addtogroup utility
/// @{

/// @brief モータ出力 -> PWM出力へ変換を行う。
struct Pwm {
  /// @brief コンストラクタ。モータ出力をセットする。
  /// @param power モータ出力
  /// @pre -1.0 <= pwm <= 1.0
  Pwm(const float power = 0.0) noexcept {
    set(power);
  }
  /// @brief モータ出力をセットする。
  /// @param power モータ出力
  void set(const float power) noexcept {
    pwm_[0] = power * (power > 0);
    pwm_[1] = -power * (-power > 0);
  }
  /// @brief PWM出力を取得する。
  /// @param n 0:正転出力,1:逆転出力
  /// @return PWM出力
  /// @post 0.0 <= 返り値 <= 1.0
  const float& operator[](const int n) const& {
    return pwm_[n];
  }
  /// @brief モータ出力をセットする。
  /// @param power モータ出力
  /// @return power
  float operator=(const float power) noexcept {
    set(power);
    return power;
  }
 private:
  float pwm_[2];
};

/// @}

}  // namespace rct

#endif  // CHASSIS_PWM_H_
