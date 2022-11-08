#ifndef CHASSIS_ODOM_H_
#define CHASSIS_ODOM_H_

#include <Chassis/CoodinateUnit.h>

#include <cmath>

namespace rct {

template<int N>
struct Odom {
  Odom(const Coodinate& pos = {}) : pos_{pos} {}
  static constexpr int size() noexcept {
    return N;
  }
  void integrate(const int (&dif_val)[N]) {
    constexpr float k = 2 * M_PI / N;
    const float tmp_rad = pos_.ang_rad;
    for(int i = 0; i < N; ++i) {
      pos_.x_milli += dif_val[i] * cos(i * k + tmp_rad);
      pos_.y_milli += dif_val[i] * sin(i * k + tmp_rad);
      pos_.ang_rad += dif_val[i];
    }
  }
  const Coodinate& get() const& noexcept {
    return pos_;
  }
  Coodinate get() const&& noexcept {
    return pos_;
  }
  void set(const Coodinate& pos) noexcept {
    pos_ = pos;
  }
 private:
  Coodinate pos_;
};

}  // namespace rct

#endif  // CHASSIS_ODOM_H_
