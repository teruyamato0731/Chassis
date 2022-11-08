# Installation
Chassisの導入方法。

## Platform IO
platformio.iniに下記を追記。
```diff
[env:nucleo_f446re]
platform = ststm32
board = nucleo_f446re
framework = mbed
+ lib_deps = https://github.com/teruyamato0731/Chassis.git
```

## Arduino IDE
ライブラリマネージャでChassis_teruと検索しインストール。 or GitHubよりダウンロードしinoと同じディレクトリに配置。
