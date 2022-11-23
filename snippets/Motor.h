#ifndef CHASSIS_MOTOR_H_
#define CHASSIS_MOTOR_H_

#ifdef __MBED__

#include <Pwm.h>
#include <mbed.h>

namespace rct {

/// @brief モータへ出力する。
/// @note コピームーブ不可
struct Motor : mbed::NonCopyable<Motor> {
  /// @brief コンストラクタ
  /// @param pinA 正転時のPWM出力ピン
  /// @param pinB 逆転時のPWM出力ピン
  Motor(const PinName pinA, const PinName pinB) : outA_{pinA}, outB_{pinB} {
    outA_.period_us(100);
    outB_.period_us(100);
  }

  /// @brief モータ出力をセットする。
  /// @param power モータ出力
  /// @pre -1.0 <= power <= 1.0
  void set_pwm(const float power) {
    pwm_ = power;
  }
  /// @brief PWMを出力する。
  void write() {
    outA_ = pwm_[0];
    outB_ = pwm_[1];
  }
  /// @brief シリアルモニタにモータ出力を表示する。
  void print() {
    printf("%d\t%d\t", int(pwm_[0] * 100), int(pwm_[1] * 100));
  }
  /// @brief モータ出力をセットしPWM出力する。
  /// @param val モータ出力
  /// @pre -1.0 <= val <= 1.0
  /// @return val
  float operator=(const float val) {
    set_pwm(val);
    write();
    return val;
  }
 private:
  mbed::PwmOut outA_;
  mbed::PwmOut outB_;
  Pwm pwm_ = {};
};

}  // namespace rct

#elif defined(ARDUINO)  // __MBED__

namespace rct {

/// @brief モータへ出力する。
struct Motor {
  /// @brief コンストラクタ
  /// @param pinA 正転時のPWM出力ピン
  /// @param pinB 逆転時のPWM出力ピン
  Motor(const int pinA, const int pinB) : pin_{pinA, pinB} {
    pinMode(pinA, OUTPUT);
    pinMode(pinB, OUTPUT);
  }
  Motor(const Motor&) = delete;
  Motor(Motor&&) = delete;
  /// @brief モータ出力をセットする。
  /// @param power モータ出力
  void set_pwm(const int power) {
    pwm_[0] = power > 0 ? power : 0;
    pwm_[1] = power > 0 ? 0 : -power;
  }
  /// @brief PWMを出力する。
  void write() {
    analogWrite(pin_[0], pwm_[0]);
    analogWrite(pin_[1], pwm_[1]);
  }
  /// @brief シリアルモニタにモータ出力を表示する。
  void print() {
    Serial.print(pwm_[0]);
    Serial.print('\t');
    Serial.print(pwm_[1]);
    Serial.print('\t');
  }
  /// @brief モータ出力をセットしPWM出力する。
  /// @param val モータ出力
  /// @return val
  int operator=(const int val) {
    set_pwm(val);
    write();
    return val;
  }
 private:
  int pin_[2];
  uint8_t pwm_[2] = {};
};

}  // namespace rct

#endif  // defined(ARDUINO)

#endif  // CHASSIS_MOTOR_H_
