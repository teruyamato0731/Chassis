# Chassis
[![version](https://img.shields.io/github/v/release/teruyamato0731/Chassis?style=flat-square)](https://github.com/teruyamato0731/Chassis/releases/latest)
[![license](https://img.shields.io/github/license/teruyamato0731/Chassis?style=flat-square)](https://github.com/teruyamato0731/Chassis/blob/main/LICENSE)
[![CI](https://img.shields.io/github/actions/workflow/status/teruyamato0731/Chassis/main.yml?label=CI&style=flat-square)](https://github.com/teruyamato0731/Chassis/actions/workflows/main.yml)

Chassisはロボコンでの足回り制御を行うためのC++ライブラリである。
ロボコン用足回りのモータ出力計算と自己位置推定による自動制御をサポートする。

[ドキュメントはこちら](https://teruyamato0731.github.io/Chassis/)

# License
Copyright (c) 2022 Yoshikawa Teru

Chassis is under the MIT License, see [LICENSE](./LICENSE).

# Developer

開発環境
- Ubuntu 22.04
- VSCode with Platform IO
- Git + Github (Pages, Projects, Work flow)
- ブランチ戦略 truck base or Github Flow
- Google Test with cmake

```
git clone https://github.com/teruyamato0731/Chassis.git
``

cmakeでテストを実行できる

```
mkdir build
cd build
cmake ..
cmake --build .
ctest
```

Semberに従っている

Conventional commit
commit_templateを使用している
```
git config commit.template .commit_template
```

# Quick Start

# Learn Frame
# Learn Chassis

# Reference
Motor 位置 順番
