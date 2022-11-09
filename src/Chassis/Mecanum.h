#ifndef CHASSIS_MECANUM_H_
#define CHASSIS_MECANUM_H_

#include <Chassis/CoodinateUnit.h>

#include <cmath>
#include <functional>
#include <utility>

namespace rct {

struct Mecanum {
  template<class F>
  Mecanum(F&& f) : f_{std::forward<F>(f)} {}
  static constexpr std::size_t size() noexcept {
    return 4;
  }
  void calc(const Velocity& vel, const float offset_rad = 0.0) {
    const float theta_rad = std::atan2(vel.y_milli, vel.x_milli);
    const float run_power = std::hypot(vel.x_milli, vel.y_milli);
    const float pwmA = run_power * std::cos(M_PI / 4 + theta_rad + offset_rad) + vel.ang_rad;
    const float pwmB = run_power * std::sin(M_PI / 4 + theta_rad + offset_rad) + vel.ang_rad;
    f_({pwmA, pwmB, pwmA, pwmB});
  }
 private:
  std::function<void(const float (&)[4])> f_;
};

}  // namespace rct

#endif  // CHASSIS_MECANUM_H_
