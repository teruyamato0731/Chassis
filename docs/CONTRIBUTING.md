[![Open in Dev Containers]](https://vscode.dev/redirect?url=vscode://ms-vscode-remote.remote-containers/cloneInVolume?url=https://github.com/teruyamato0731/Chassis)

[Open in Dev Containers]: https://img.shields.io/static/v1?label=Dev%20Containers&message=Open&color=blue&logo=visualstudiocode

# Welcome to Chassis contributing guide
このプロジェクトのバージョニングは [Semantic versioning](https://semver.org/lang/ja/) に従っている。

コミットメッセージは [Conventional commit](https://www.conventionalcommits.org/ja/v1.0.0/) に従っている。

ブランチ戦略は GitHub Flow を取っている。

Unit Test には Google Test を使用している。

Documentation には Doxygen と GitHub Pages を使用している。

## Quick Start

### Issues
- ドキュメントの不備
- 不具合を見つけた場合
- 新機能の要望

はじめにIssueが既に存在するかを検索し、関連するIssueが存在しなかった場合に新しいIssueを作成すること。

### Make Changes
1. Docker, vscode をインストールする。
1. ページ上部の Open in Dev Containers または [こちら](https://vscode.dev/redirect?url=vscode://ms-vscode-remote.remote-containers/cloneInVolume?url=https://github.com/teruyamato0731/Chassis) を押す。
1. 任意の変更を行う。
1. scripts/test.bash を実行してコードのテストを行う。
    ```bash
    scripts/test.bash
    ```
1. scripts/deploy.bash を実行すると、 Doxygen によるドキュメントの生成が行われる。
  http://localhost:8000 より WEB ページの出力が確認できる。
    ```bash
    scripts/deploy.bash
    ```

## Library Manager
このライブラリは [Arduino Library Manager](https://www.arduinolibraries.info/libraries/chassis) に登録されており、[logはここ](https://downloads.arduino.cc/libraries/logs/github.com/teruyamato0731/Chassis/)から確認できる。

[Platform IOのレジストリ](https://registry.platformio.org/libraries/teruyamato0731/Chassis)にも登録されている。

## CI/CD
<image src="./ci.drawio.svg" style="padding: 1em" alt="CI,CDのフロー図" />

## 開発者の環境
- Ubuntu 22.04
- VSCode + Platform IO
- Git + Github
