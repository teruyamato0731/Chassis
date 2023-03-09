# Welcome to Chassis contributing guide
このプロジェクトのバージョニングは[Semantic versioning](https://semver.org/lang/ja/)に従っている。

コミットメッセージは[Conventional commit](https://www.conventionalcommits.org/ja/v1.0.0/)に従っている。

ブランチ戦略はGithub Flowを取っている。

## Quick Start

### Issues
- ドキュメントの不備
- 不具合を見つけた場合
- 新機能の要望

はじめにすでにIssueが存在するかを検索すること。

関連するIssueが存在しない場合に、Issue templateを使用して新しいIssueを作成する。

### Make Changes
```
git clone https://github.com/teruyamato0731/Chassis.git
```

Google Test を導入しており、cmakeでテストを実行できる。
```
mkdir -p build && cd "$_"
cmake ..
cmake --build .
ctest
```

[commit.template](./.commit_template)を使用しており、下記コマンドで導入できる。
```
git config commit.template .commit_template
```

PRを提出する前に以下のことを確認してください
- [ ] エラーや警告がなくコンパイルが通る
- [ ] Doxygenコメントが追加されている
- [ ] Doxygenのビルドが通る
- [ ] ユニットテストが追加されている
- [ ] ユニットテストが通る

## Library Manager
このライブラリは[Arduino Library Manager](https://www.arduinolibraries.info/libraries/chassis)に登録されており、[logはここ](https://downloads.arduino.cc/libraries/logs/github.com/teruyamato0731/Chassis/)から確認できる。

[Platform IOのレジストリ](https://registry.platformio.org/libraries/teruyamato0731/Chassis)にも登録されている。

## CI/CD
<image src="./dox/ci.drawio.svg" style="padding: 1em" alt="CI,CDのフロー図" />

## 開発者の環境
- Ubuntu 22.04
- VSCode + Platform IO
- Git + Github
