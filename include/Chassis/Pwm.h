#ifndef CHASSIS_IMOTOR_H_
#define CHASSIS_IMOTOR_H_

namespace rct {

template<int N = 5, int M = 100>
struct Pwm {
  static_assert(M != 0);
  static constexpr float lower_power_limit() noexcept {
    return N / (float)M;
  }
  void set(const float power) noexcept {
    // if(lower_power_limit() < power) {
    //   // 最低値より大きい時
    //   pwm_[0] = power;
    //   pwm_[1] = 0;
    // } else if(power < -lower_power_limit()) {
    //   // 負の最低値より小さい時
    //   pwm_[0] = 0;
    //   pwm_[1] = -1 * power;
    // } else {
    //   // 絶対値が最低値以下のとき
    //   pwm_[0] = 0;
    //   pwm_[1] = 0;
    // }

    pwm_[0] = power * (power > lower_power_limit());
    pwm_[1] = -power * (-power > lower_power_limit());
  }
  float& operator[](const int n) {
    return pwm_[n];
  }
  const Pwm& operator=(const float power) noexcept {
    set(power);
    return *this;
  }
  float pwm_[2];
};

template<int M>
struct Pwm<0, M> {
  static constexpr float lower_power_limit() noexcept {
    return 0;
  }
  void set(const float power) noexcept {
    // if(0 < power) {
    //   // 生の値
    //   pwm_[0] = power;
    //   pwm_[1] = 0;
    // } else if(power < -0) {
    //   // 負の値
    //   pwm_[0] = 0;
    //   pwm_[1] = -1 * power;
    // } else {
    //   // 0
    //   pwm_[0] = 0;
    //   pwm_[1] = 0;
    // }

    pwm_[0] = power * (power > 0);
    pwm_[1] = -power * (-power > 0);
  }
  float& operator[](const int n) {
    return pwm_[n];
  }
  const Pwm& operator=(const float power) noexcept {
    set(power);
    return *this;
  }
  float pwm_[2];
};

}  // namespace rct

#endif  // CHASSIS_IMOTOR_H_
