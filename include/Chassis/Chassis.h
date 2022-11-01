#ifndef RCT_CHASSIS_H_
#define RCT_CHASSIS_H_

#include <Chassis/CoodinateUnit.h>
#include <Chassis/Pid.h>

#include <chrono>
#include <cmath>
#include <cstdint>

namespace rct {

template<class T, bool B1 = true, bool B2 = true>
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

template<class T>
struct Chassis<T, true, false> {
  template<class F>
  ChassisAuto(F&& f, const PidGain& pos_gain) : t_{std::forward<F>(f)}, pos_pid_{pos_gain} {}
  void abs_move(const Coodinate& dst, const Coodinate& pos, const std::chrono::microseconds& delta_time) {
    const auto out_vel = pos_pid_.calc(dst, pos, delta_time) / std::chrono::seconds{1};
    t_.calc(out_vel);
  }
 private:
  T t_;
  Pid<Coodinate> pos_pid_;
};
template<class T>
using ChassisAuto = Chassis<T, true, false>;

template<class T>
struct Chassis<T, false, true> {
  template<class F>
  ChassisPid(F&& f, const PidGain& vel_gain) : t_{std::forward<F>(f)}, vel_pid_{vel_gain} {}
  void pid_move(const Velocity& tag_vel, const Velocity& now_vel, const std::chrono::microseconds& delta_time) {
    const auto out_vel = vel_pid_.calc(tag_vel, now_vel, delta_time);
    t_.calc(out_vel);
  }
 private:
  T t_;
  Pid<Velocity> vel_pid_;
};
template<class T>
using ChassisPid = Chassis<T, false, true>;

}  // namespace rct

#endif  // RCT_CHASSIS_H_
