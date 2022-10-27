#ifndef CHASSIS_OMNI_H_
#define CHASSIS_OMNI_H_

#include <Chassis/CoodinateUnit.h>

#include <cmath>
#include <functional>
#include <utility>

namespace rct {

template<int N>
struct Omni {
  template<class F>
  Omni(F&& f) : f_{std::forward<F>(f)} {}
  static constexpr int size() noexcept {
    return N;
  }
  void calc(const Velocity& vel, const float offset_rad = {}) {
    const float theta_rad = std::atan2(vel.y_milli, vel.x_milli);
    const float run_power = std::hypot(vel.x_milli, vel.y_milli);
    float pwms[N];
    for(int i = 0; i < N; ++i) {
      constexpr auto k = 2 * M_PI / N;
      // sin(x) + cos(x) = 2^(1/2) * sin(x+pi/4)
      const auto pwm = run_power * std::cos(i * k + theta_rad + offset_rad) + vel.ang_rad;
      // const auto pwm = run_power * std::cos(i * k + theta_rad + offset_rad) +
      //                  run_power * std::sin(i * k + theta_rad + offset_rad) + vel.ang_rad;
      pwms[i] = pwm;
    }
    f_(pwms);
  }
 private:
  std::function<void(const float (&)[N])> f_;
};

}  // namespace rct

#endif  // CHASSIS_OMNI_H_
