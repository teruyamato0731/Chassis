# Chassis
Chassisはロボコンでの足回り制御を行うためのC++ライブラリである。

# Features
- 以下の足回りが制御できる。
  - 三輪オムニ, 四輪オムニ (任意輪のオムニ)
  - メカナム
- 自動制御ができる。
- モータへのPWM出力はcallback関数で受け持つため、任意のフレームワークで使用できる。
- 自己位置は関数の引数で受け渡すため、任意のセンサとフィルタの組み合わせで使用できる。

# Requirement
- Platform IO の入った VSCode。もしくは Arduino IDE
- C++17で動かせるマイコン(ArduinoやMbedなど)

# Installation
[導入方法はこちら](./docs/Installation.md)

# Usage
[使用方法はこちら](./docs/Usage.md)

# License
Copyright (c) 2022 Yoshikawa Teru

Chassis is under the MIT License, see LICENSE.
