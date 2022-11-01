#ifndef RCT_CHASSIS_H_
#define RCT_CHASSIS_H_

#include <Chassis/CoodinateUnit.h>
#include <Chassis/Pid.h>

#include <chrono>
#include <cmath>
#include <cstdint>

namespace rct {

template<class T>
struct Chassis {
  template<class F>
  Chassis(F&& f, const PidGain& vel_gain, const PidGain& pos_gain)
      : t_{std::forward<F>(f)}, vel_pid_{vel_gain}, pos_pid_{pos_gain} {}
  void pid_move(const Velocity& tag_vel, const Velocity& now_vel, const std::chrono::microseconds& delta_time) {
    const auto out_vel = vel_pid_.calc(tag_vel, now_vel, delta_time);
    t_.calc(out_vel);
  }
  void abs_move(const Coodinate& dst, const Coodinate& pos, const std::chrono::microseconds& delta_time) {
    const auto out_vel = pos_pid_.calc(dst, pos, delta_time) / std::chrono::seconds{1};
    t_.calc(out_vel);
  }
 private:
  T t_;
  Pid<Velocity> vel_pid_;
  Pid<Coodinate> pos_pid_;
};

}  // namespace rct

#endif  // RCT_CHASSIS_H_
