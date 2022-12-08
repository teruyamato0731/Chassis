\mainpage Introduction
[Chassis](https://github.com/teruyamato0731/Chassis)はロボコンでの足回り制御を行うためのC++ライブラリである。
ロボコン用足回りのモータ出力計算と自己位置推定による自動制御をサポートする。

\todo Demo

## Features
- 三輪オムニや四輪オムニ、メカナム、四輪独立ステアリングなどのモータ出力計算に対応。
- エンコーダのオドメトリを用いた自己位置推定に対応。
- 自己位置推定とPID制御による自動制御に対応。<br>
  自己位置推定は任意のセンサとフィルタの組み合わせで実装できる。

## Supported Environment
- Platform IO の入った VSCode。もしくは Arduino IDE。
- C++17で動くフレームワークとマイコン。<br>ArduinoやMbedで動くnucleo, esp32, teensyなどに対応。

## Licensing
Copyright (c) 2022 Yoshikawa Teru

Chassis is under the MIT License, see [LICENSE](https://github.com/teruyamato0731/Chassis/blob/main/LICENSE).

---
<span class="next_section_button">\ref Installation</span>

- \ref Installation
- \ref Usage

\tableofcontents
