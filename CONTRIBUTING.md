# Welcome to Chassis contributing guide
このプロジェクトのバージョニングは[Semantic versioning](https://semver.org/lang/ja/)に従っている。

コミットメッセージは[Conventional commit](https://www.conventionalcommits.org/ja/v1.0.0/)に従っており、[commit.template](./.commit_template)を使用している。

ブランチ戦略はGithub Flowを取っている。

## Quick Start

### Issues
- ドキュメントの不備
- 不具合を見つけた場合
- 新機能の要望

はじめにすでにIssueが存在するかを検索してください。

関連するIssueが存在しない場合は、Issue templateを使用して新しいIssueを作成してください。

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

PRを提出する前に以下のことを確認してください
- [ ] エラーや警告がなくコンパイルが通る
- [ ] Doxygenコメントが追加されている
- [ ] Doxygenのビルドが通る
- [ ] ユニットテストが追加されている
- [ ] ユニットテストが通る

## 開発者の環境
- Ubuntu 22.04
- VSCode + Platform IO
- Git + Github
