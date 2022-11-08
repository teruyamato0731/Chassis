# Odomクラスのリファレンス

`#include <Chassis/Odom.h>`

```C++ Chassis/Odom.h
template<int N>
struct Odom {
  Odom(const Coodinate& pos = {});
  static constexpr int size();
  void integrate(const int (&dif_val)[N]);
  const Coodinate& get() const&;
  Coodinate get() const&&;
  void set(const Coodinate& pos);
};
```

# 基本的な使い方

## インスタンスの生成

## 動作

# 詳細な説明

# メンバ関数

## Odom
コンストラクタ。
