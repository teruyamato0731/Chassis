\mainpage Introduction
[Chassis](https://github.com/teruyamato0731/Chassis)はロボコンでの足回り制御を行うためのC++ライブラリである。
ロボコン用足回りのモータ出力計算と自己位置推定による自動制御をサポートする。

\todo Demo

# Features
- 三輪オムニや四輪オムニ、メカナムなどのモータ出力計算に対応。
- エンコーダのオドメトリを用いた自己位置推定に対応。
- 自己位置推定とPID制御による自動制御に対応。<br>
  自己位置推定は任意のセンサとフィルタの組み合わせで実装できる。

# Supported Environment
- Platform IO の入った VSCode。もしくは Arduino IDE。
- C++17で動くフレームワークとマイコン。<br>ArduinoやMbedで動くnucleo, esp32, teensyなどに対応。

# License
Copyright (c) 2022 Yoshikawa Teru

Chassis is under the MIT License, see [LICENSE](https://github.com/teruyamato0731/Chassis/blob/master/LICENSE).

---

- \ref Installation
- \ref Usage
- [ChassisのGithubページ](https://github.com/teruyamato0731/Chassis)

\tableofcontents
