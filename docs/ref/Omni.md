# Omniクラスのリファレンス
N輪オムニの制御を行うクラス。

`#include <Chassis/Omni.h>`

```C++
template<int N>
struct Omni {
  static_assert(N > 0);
  template<class F> Omni(F&& f);
  static constexpr int size() noexcept;
  void calc(const Velocity& vel, float offset_rad = 0.0);
};
```

# 基本的な使い方

## インスタンスの生成
1. templateパラメータ N にモータ数を与える。
1. モータへの出力を行うcallback関数を作成。<br>
  callback関数の型はvoid(const float(&)[N])<br>
  N要素float配列のconst参照を受け取り、voidを返す関数型。
1. 引数にcallback関数を渡す。

Arduinoでの例
``` C++:Arduino
Omni<3> omni{[](const float(&pwms)[3]){}};
```

Mbedでの例
``` C++:Mbed
AnalogOut pins {A0,A1,A2, A3};
Omni<4> omni{[](const float(&pwms)[4]){}};
```

## 動作

# 詳細な説明

# メンバ関数

## Omni
コンストラクタ。
callback関数をセットする。

## size
モータ数 N を返す。

## calc
モータへのPWM出力を計算する。
その後callback関数にPWM出力を渡す。
