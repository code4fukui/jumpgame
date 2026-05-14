# jumpgame


raylib([https://www.raylib.com/](https://www.raylib.com/))を使用して作成された、敵を避けながらジャンプするシンプルな2Dアクションゲームです。

![ゲームプレイスクリーンショット](screenshots/gameplay.png)

## ゲームの遊び方

- 青いボールを操作します。
- `Space`キーを押してジャンプし、右から近づいてくる赤い敵を避けます。
- 地面にいる時のみジャンプ可能です。
- 敵を成功裏に避けたたびにスコアが増加します。
- スコアが上がると敵の移動速度が早くなります。
- 敵と接触するとゲームオーバーになります。
- 「GAME OVER」画面で`Space`キーを押すとリスタートします。

## はじめに

### 必要条件

- Xcode Command Line ToolsがインストールされたmacOS

### ビルド

含まれる`raylib`ライブラリは静的リンクされています。ビルドスクリプトを実行してください:

```sh
sh build.sh
```

### 実行

```sh
./jumpgame
```

このREADMEに使用されているスクリーンショットを生成するには、以下のコマンドを使用してください:

```sh
./jumpgame --capture screenshots/gameplay.png
```

## ライセンス

ゲームのソースコード(`game.c`)はCC0 1.0 Universalライセンスで公開されています。バンドルされたraylibライブラリはzlib/libpngライセンスの下で提供されています。詳細は`raylib.h`ヘッダファイルおよび[raylibウェブサイト](https://www.raylib.com/license.html)を参照してください。