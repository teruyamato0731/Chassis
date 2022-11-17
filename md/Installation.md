\page Installation Chassisの導入方法
# Platform IO
platformio.iniに下記のようにlib_depsを追記。
```diff
[env:nucleo_f446re]
platform = ststm32
board = nucleo_f446re
framework = mbed
+ lib_deps = https://github.com/teruyamato0731/Chassis.git
+ build_flags = -std=gnu++17
+ build_unflags = -std=gnu++14
```

# Arduino IDE
Arduino IDEのライブラリマネージャでChassisと検索しインストール。<br>
もしくはGitHubよりChassisをダウンロードしinoと同じディレクトリにソースファイルを配置。

---

- \ref index
- \ref Usage

\tableofcontents
