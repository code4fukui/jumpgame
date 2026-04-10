# Jump Game

`raylib` を使って作った、ボールをジャンプさせて敵を避けるシンプルなアクションゲームです。

![ゲーム画面](screenshots/gameplay.png)

## ゲーム内容

- 青い球を操作します
- `Space` キーでジャンプします
- 右から流れてくる敵にぶつかるとゲームオーバーです
- 敵を避けるたびにスコアが増えます
- ゲームオーバー後に `Space` キーでリスタートできます

## ファイル構成

- `game.c` : ゲーム本体
- `raylib.h` : `raylib` ヘッダ
- `libraylib.a` : `raylib` 静的ライブラリ
- `screenshots/gameplay.png` : README 用のゲーム画面キャプチャ

## ビルド方法

macOS でのビルド例です。

```sh
sh build.sh
```

## 実行方法

```sh
./jumpgame
```

## 操作方法

- `Space` : ジャンプ
- ウィンドウを閉じる : 終了

## 仕様

- 地面の上でのみジャンプできます
- 敵は画面右から左へ移動します
- スコアが上がると敵の速度も少しずつ上がります

## Codex で作成した手順

ターミナルを開いて、`Codex CLI` を使って今回の内容を再現する場合の流れです。

1. ターミナルを開く
2. [OpenAI](https://openai.com/ja-JP/) 公式の [Codex ドキュメント](https://developers.openai.com/codex/quickstart)に従って `Codex CLI` をインストールする
3. 作業用ディレクトリを作成して移動する

```sh
mkdir jumpgame
cd jumpgame
```

4. `raylib.h` と `libraylib.a` を配置した状態で `codex` を起動する
5. 以降、Codex に次の依頼を順に出す

```text
raylibを使って丸い球がスペースキーでジャンプして、横からくる敵を避けるゲームをつくって
README.md 日本語で書いて
raylibのライセンスについても確認して追記して
game.c は、CC0またはそれ相当のものとします。LICENSE追加して
実行ファイルはgitに含めないようにして
ビルドスクリプトは1行にして
キャプチャーを撮ってREADME.mdに加えて
今回 codex で作った手順をREADMEの中にまとめて
ターミナルを開き、condexをインストールするところからの手順にして
```

6. ネイティブ版をビルドして実行する

```sh
sh build.sh
./jumpgame
```

7. README 用キャプチャを撮る場合は次を実行する

```sh
./jumpgame --capture screenshots/gameplay.png
```

補足:

- `Codex CLI` の導入方法や最新の利用条件は変更される可能性があるため、インストール部分は OpenAI 公式ドキュメントを参照してください
- OpenAI 公式ドキュメントでは、Codex は CLI や IDE から利用できると案内されています
- OpenAI 公式ドキュメントでは、MCP 設定例として `codex mcp add ...` 形式のコマンドが案内されています

## ライセンス

このゲーム本体のコード `game.c` は、`CC0 1.0 Universal` 相当として公開しています。詳細は `LICENSE` を参照してください。

同梱している `raylib` は、公式情報では `unmodified zlib/libpng license` で配布されています。商用利用、改変、再配布が可能な、制約の少ないライセンスです。

主な条件は次のとおりです。

- `raylib` の作者を自分だと偽らないこと
- 改変版を配布する場合は、元の版と明確に区別すること
- ソース配布時にライセンス表記を削除または改変しないこと

`libraylib.a` や `raylib.h` は `CC0` の対象外です。再配布する場合は、`raylib` のライセンス表記もあわせて含めるのが適切です。

参考:

- raylib license: https://www.raylib.com/license.html
- raylib GitHub repository: https://github.com/raysan5/raylib
