#ifndef RCT_CHASSIS_AUTO_H_
#define RCT_CHASSIS_AUTO_H_
/// @file
/// @brief 足回りの位置のPID制御を行うChassisAutoを提供する。
#include <CoodinateUnit.h>
#include <Pid.h>

#include <chrono>
#include <cmath>
#include <cstdint>

namespace rct {

/// @addtogroup chassis
/// @{

/// @brief 足回りの位置のPID制御を行う。
/// @tparam T
template<class T>
struct ChassisAuto {
  template<class F>
  ChassisAuto(F&& f, const PidGain& pos_gain) : t_{std::forward<F>(f)}, pos_pid_{pos_gain} {}
  void auto_move(const Coodinate& dst, const Coodinate& pos, const std::chrono::microseconds& delta_time) {
    const auto out_vel = pos_pid_.calc(dst, pos, delta_time) / std::chrono::seconds{1};
    t_.move(out_vel);
  }

 private:
  T t_;
  Pid<Coodinate> pos_pid_;
};

/// @}

}  // namespace rct

#endif  // RCT_CHASSIS_AUTO_H_
