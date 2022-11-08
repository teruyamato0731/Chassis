# Pidクラスのリファレンス

`#include <Chassis/Pid.h>`

```C++ Chassis/Pid.h

template<class T>
struct Pid {
  Pid(const PidGain& pid_gain);
  T calc(const T& dst, const T& now, const std::chrono::microseconds& delta_time);
  void refresh();
  void set_pid_gain(const PidGain& pid_gain);
};

```

# 基本的な使い方

## インスタンスの生成

## 動作

# 詳細な説明

# メンバ関数

## Pid
コンストラクタ。
