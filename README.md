# jumpgame

> 日本語のREADMEはこちらです: [README.ja.md](README.ja.md)

A simple 2D action game where you jump to avoid enemies, built with [raylib](https://www.raylib.com/).


![Gameplay Screenshot](screenshots/gameplay.png)


## How to Play

-   You control the blue ball.
-   Press `Space` to jump and avoid the red enemies that approach from the right.
-   You can only jump when on the ground.
-   Your score increases for each enemy you successfully dodge.
-   As your score goes up, the enemies move faster.
-   If you collide with an enemy, the game is over.
-   Press `Space` on the "GAME OVER" screen to restart.

## Getting Started

### Prerequisites

-   macOS with Xcode Command Line Tools installed.

### Build

The included `raylib` library is statically linked. Simply run the build script:

```sh
sh build.sh
```

### Run

```sh
./jumpgame
```

You can also generate the screenshot used in this README with the following command:

```sh
./jumpgame --capture screenshots/gameplay.png
```

## License

The game source code (`game.c`) is released under the CC0 1.0 Universal license. The bundled raylib library is under the zlib/libpng license. See the `raylib.h` header and [raylib website](https://www.raylib.com/license.html) for more details.