#ifndef CHASSIS_PID_H_
#define CHASSIS_PID_H_

#include <chrono>
#include <optional>

namespace rct {

struct PidGain {
  float kp;
  float ki;
  float kd;
};

template<class T, decltype(std::declval<T&>() = std::declval<T>() + std::declval<T>(),
                           std::declval<T&>() = std::declval<T>() - std::declval<T>(),
                           std::declval<T&>() = std::declval<T>() * std::declval<float>(),
                           std::declval<T&>() = std::declval<T>() / std::declval<float>(), T{}, nullptr) = nullptr>
struct Pid {
  Pid(const PidGain& pid_gain) noexcept : pid_gain_{pid_gain} {}
  T calc(T dst, T now, std::chrono::microseconds delta_time) {
    const float sec = std::chrono::duration<float>{delta_time}.count();
    const T proportional = dst - now;
    integral_ += proportional * sec;
    const T differential = pre_ ? (now - *pre_) / sec : T{};
    pre_ = now;
    return proportional * pid_gain_.kp + integral_ * pid_gain_.ki + differential * pid_gain_.kd;
  }
  void refresh() noexcept {
    integral_ = T{};
    pre_ = std::nullopt;
  }
  void set_pid_gain(const PidGain& pid_gain) noexcept {
    pid_gain_ = pid_gain;
    refresh();
  }
 private:
  PidGain pid_gain_;
  T integral_{};
  std::optional<T> pre_{};
};

}  // namespace rct

#endif  // CHASSIS_PID_H_
