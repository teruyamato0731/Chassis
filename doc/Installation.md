\page Installation Chassisの導入方法
## Platform IO
[platformio.ini](\ref snippets/platformio.ini)に下記のようにlib_deps, build_flags, build_unflagsを追記。

<!-- <div class="fragment">
<div class="line">[env:nucleo_f446re]</div>
<div class="line">platform = ststm32</div>
<div class="line">board = nucleo_f446re</div>
<div class="line">framework = mbed</div>
<div class="line" style="background-color:rgba(46,160,67,0.15);">+ lib_deps = https://github.com/teruyamato0731/Chassis.git</div>
<div class="line" style="background-color:rgba(46,160,67,0.15);">+ build_flags = -std=gnu++17</div>
<div class="line" style="background-color:rgba(46,160,67,0.15);">+ build_unflags = -std=gnu++14</div>
</div> -->

\snippet snippets/platformio.ini config

## Arduino IDE
Arduino IDEのライブラリマネージャでChassisと検索しインストール。<br>
もしくはGitHubよりChassisをダウンロードしinoと同じディレクトリにソースファイルを配置。

---
<span class="next_section_button">\ref Usage</span>

- \ref index
- \ref Usage

\tableofcontents
