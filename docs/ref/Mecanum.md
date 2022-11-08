# Mecanumクラスのリファレンス

`#include <Chassis/Mecanum.h>`

```C++ Chassis/Mecanum.h
struct Mecanum {
  template<class F> Mecanum(F&& f);
  static constexpr int size() noexcept;
  void calc(const Velocity& vel, float offset_rad = 0.0);
};
```

# 基本的な使い方

## インスタンスの生成
1. モータへの出力を行うcallback関数を作成。<br>
  callback関数の型はvoid(const float(&)[4])<br>
  4要素float配列のconst参照を受け取り、voidを返す関数型。
1. 引数にcallback関数を渡す。

Arduinoでの例
``` C++ Arduino
Mecanum mecanum{[](const float(&pwms)[4]){}};
```

Mbedでの例
``` C++ Mbed
AnalogOut pins {A0,A1,A2};
Mecanum mecanum{[](const float(&pwms)[4]){}};
```

## 動作

# 詳細な説明

# メンバ関数

## Mecanum
コンストラクタ。
