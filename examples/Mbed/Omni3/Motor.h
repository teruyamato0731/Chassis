#ifndef MOTOR_H_
#define MOTOR_H_

/// @file
/// @brief Motor出力

#include <Pwm.h>
#include <mbed.h>

struct Motor {
  Motor(const PinName pinA, const PinName pinB) : outA_{pinA}, outB_{pinB} {
    outA_.period_us(100);
    outB_.period_us(100);
  }
  Motor(const Motor&) = delete;
  Motor(Motor&&) = delete;
  void set_pwm(const float power) {
    pwm_ = power;
    outA_ = pwm_[0];
    outB_ = pwm_[1];
  }
  void print() {
    printf("%d\t%d\t", int(pwm_[0] * 100), int(pwm_[1] * 100));
  }
  float operator=(const float val) {
    set_pwm(val);
    return val;
  }
 private:
  mbed::PwmOut outA_;
  mbed::PwmOut outB_;
  rct::Pwm pwm_ = {};
};

#endif  // MOTOR_H_
