# Chassisクラスのリファレンス

`#include <Chassis/Chassis.h>`

```C++ Chassis/Chassis.h
template<class T>
struct Chassis {
  template<class F>
  Chassis(F&& f, const PidGain& vel_gain, const PidGain& pos_gain);
  void pid_move(const Velocity& tag_vel, const Velocity& now_vel, const std::chrono::microseconds& delta_time,
                float offset_rad = 0.0);
  void auto_move(const Coodinate& dst, const Coodinate& pos, const std::chrono::microseconds& delta_time);
};
```

# 基本的な使い方

## インスタンスの生成

## 動作

# 詳細な説明

# メンバ関数

## Chassis
コンストラクタ。
