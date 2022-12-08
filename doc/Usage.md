\page Usage Chassisの使用方法
Chassisを用いて手動制御、自己位置推定、自動制御を行う方法を示す。
また下記の例では[Motor.h](\ref snippets/Motor.h)を使用している。

## 手動制御
[frameモジュール](\ref frame)を用いる。
例は[3輪オムニ](\ref rct::Omni)。

インスタンスの生成
\snippet examples/Mbed/Omni3/main.cpp construct

移動速度を渡してモータ出力を計算しモータにセットする。
\snippet examples/Mbed/Omni3/main.cpp move

<!-- \snippet{lineno} examples/Mbed/Omni3/main.cpp test -->

<!-- \ref examples/Mbed/Omni3/main.cpp -->
<!-- \include{lineno} examples/Mbed/Omni3/main.cpp -->

## 自己位置推定
[localizationモジュール](\ref localization)を用いる。
\include{lineno} examples/Mbed/Odom/main.cpp

## 自動制御
[chassisモジュール](\ref chassis)を用いる。
\include{lineno} examples/Mbed/Chassis/main.cpp

## 4輪独立ステアリング
インスタンスの生成
\snippet examples/Mbed/4WDS/main.cpp construct
出力
\snippet examples/Mbed/4WDS/main.cpp move

---
<span class="next_section_button">[utilityモジュール](\ref utility)</span>

- \ref index
- \ref Installation

\tableofcontents
