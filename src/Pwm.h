#ifndef CHASSIS_PWM_H_
#define CHASSIS_PWM_H_
/// @file
/// @brief Pwm クラスを提供する。

namespace rct {

/// @addtogroup utility
/// @{

/// @brief モータ出力 -> PWM出力へ変換を行う。
struct Pwm {
  Pwm(const float pwm = 0.0) noexcept {
    set(pwm);
  }
  void set(const float power) noexcept {
    pwm_[0] = power * (power > 0);
    pwm_[1] = -power * (-power > 0);
  }
  float& operator[](const int n) & {
    return pwm_[n];
  }
  float operator=(const float power) noexcept {
    set(power);
    return power;
  }
  float pwm_[2];
};

/// @}

}  // namespace rct

#endif  // CHASSIS_PWM_H_
