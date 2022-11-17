#ifndef RCT_CHASSIS_PID_H_
#define RCT_CHASSIS_PID_H_
/// @file
/// @brief 足回りの速度のPID制御を行うChassisPidを提供する。
#include <CoodinateUnit.h>
#include <Pid.h>

#include <chrono>
#include <cmath>
#include <cstdint>

namespace rct {

/// @addtogroup chassis
/// @{

/// @brief 足回りの速度のPID制御を行う。
/// @tparam T
template<class T>
struct ChassisPid {
  template<class F>
  ChassisPid(F&& f, const PidGain& vel_gain) : t_{std::forward<F>(f)}, vel_pid_{vel_gain} {}
  void pid_move(const Velocity& tag_vel, const Velocity& now_vel, const std::chrono::microseconds& delta_time) {
    const auto out_vel = vel_pid_.calc(tag_vel, now_vel, delta_time);
    t_.move(out_vel);
  }

 private:
  T t_;
  Pid<Velocity> vel_pid_;
};

/// @}

}  // namespace rct

#endif  // RCT_CHASSIS_PID_H_
