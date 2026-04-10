#include "raylib.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 540
#define GROUND_HEIGHT 110
#define PLAYER_RADIUS 26.0f
#define PLAYER_X 160.0f
#define GRAVITY 1800.0f
#define JUMP_VELOCITY -720.0f
#define ENEMY_WIDTH 36.0f
#define ENEMY_HEIGHT 72.0f
#define ENEMY_MIN_SPEED 320.0f
#define ENEMY_MAX_SPEED 540.0f

typedef struct Enemy {
    float x;
    float speed;
    bool passed;
} Enemy;

typedef struct GameState {
    float playerY;
    float playerVelocityY;
    Enemy enemy;
    int score;
    bool gameOver;
} GameState;

static float GroundY(void) {
    return (float)SCREEN_HEIGHT - GROUND_HEIGHT;
}

static void ResetEnemy(Enemy *enemy, int score) {
    enemy->x = (float)SCREEN_WIDTH + GetRandomValue(120, 420);
    enemy->speed = ENEMY_MIN_SPEED + (float)GetRandomValue(0, 140) + (float)score * 8.0f;
    if (enemy->speed > ENEMY_MAX_SPEED + (float)score * 3.0f) {
        enemy->speed = ENEMY_MAX_SPEED + (float)score * 3.0f;
    }
    enemy->passed = false;
}

static void ResetGame(GameState *game) {
    game->playerY = GroundY() - PLAYER_RADIUS;
    game->playerVelocityY = 0.0f;
    game->score = 0;
    game->gameOver = false;
    ResetEnemy(&game->enemy, game->score);
}

static Rectangle GetEnemyRect(const Enemy *enemy) {
    return (Rectangle) {
        enemy->x,
        GroundY() - ENEMY_HEIGHT,
        ENEMY_WIDTH,
        ENEMY_HEIGHT
    };
}

static void DrawGame(const GameState *game) {
    ClearBackground((Color) { 245, 250, 255, 255 });

    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, (Color) { 230, 244, 255, 255 });
    DrawCircleGradient(SCREEN_WIDTH - 160, 100, 46, (Color) { 255, 224, 120, 255 }, (Color) { 255, 194, 70, 255 });

    DrawRectangle(0, (int)GroundY(), SCREEN_WIDTH, GROUND_HEIGHT, (Color) { 92, 148, 92, 255 });
    DrawRectangle(0, (int)GroundY(), SCREEN_WIDTH, 14, (Color) { 70, 115, 70, 255 });

    for (int i = 0; i < SCREEN_WIDTH; i += 64) {
        DrawRectangle(i, (int)GroundY() + 18, 28, 12, (Color) { 110, 170, 110, 255 });
    }

    DrawCircleV((Vector2) { PLAYER_X, game->playerY }, PLAYER_RADIUS, (Color) { 70, 130, 220, 255 });
    DrawCircleLines((int)PLAYER_X, (int)game->playerY, PLAYER_RADIUS, (Color) { 20, 60, 120, 255 });
    DrawCircle((int)(PLAYER_X - 8), (int)(game->playerY - 6), 4, WHITE);

    Rectangle enemyRect = GetEnemyRect(&game->enemy);
    DrawRectangleRounded(enemyRect, 0.25f, 6, (Color) { 220, 80, 80, 255 });
    DrawRectangleLinesEx(enemyRect, 2.0f, (Color) { 130, 20, 20, 255 });
    DrawCircle((int)(enemyRect.x + 10), (int)(enemyRect.y + 18), 4, WHITE);
    DrawCircle((int)(enemyRect.x + enemyRect.width - 10), (int)(enemyRect.y + 18), 4, WHITE);

    DrawText(TextFormat("SCORE %d", game->score), 30, 28, 34, (Color) { 32, 56, 110, 255 });
    DrawText("SPACE: JUMP", 30, 70, 24, (Color) { 32, 56, 110, 255 });

    if (game->gameOver) {
        DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, (Color) { 0, 0, 0, 90 });
        DrawText("GAME OVER", SCREEN_WIDTH / 2 - 130, 170, 50, WHITE);
        DrawText(TextFormat("FINAL SCORE %d", game->score), SCREEN_WIDTH / 2 - 130, 240, 32, WHITE);
        DrawText("PRESS SPACE TO RETRY", SCREEN_WIDTH / 2 - 170, 300, 28, WHITE);
    }
}

int main(int argc, char **argv) {
    bool captureMode = false;
    const char *capturePath = "screenshot.png";

    if (argc >= 3 && strcmp(argv[1], "--capture") == 0) {
        captureMode = true;
        capturePath = argv[2];
    }

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Jump Ball");
    SetTargetFPS(60);

    GameState game = {0};
    ResetGame(&game);

    if (captureMode) {
        game.score = 7;
        game.playerY = GroundY() - PLAYER_RADIUS - 90.0f;
        game.enemy.x = PLAYER_X + 240.0f;
        game.enemy.speed = ENEMY_MIN_SPEED + 80.0f;
        game.enemy.passed = false;

        RenderTexture2D target = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);
        BeginTextureMode(target);
        DrawGame(&game);
        EndTextureMode();

        Image image = LoadImageFromTexture(target.texture);
        ImageFlipVertical(&image);
        ExportImage(image, capturePath);
        UnloadImage(image);
        UnloadRenderTexture(target);
        CloseWindow();
        return 0;
    }

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        bool jumpPressed = IsKeyPressed(KEY_SPACE);

        if (game.gameOver) {
            if (jumpPressed) {
                ResetGame(&game);
            }
        } else {
            bool onGround = game.playerY >= GroundY() - PLAYER_RADIUS - 0.5f;
            if (jumpPressed && onGround) {
                game.playerVelocityY = JUMP_VELOCITY;
            }

            game.playerVelocityY += GRAVITY * dt;
            game.playerY += game.playerVelocityY * dt;
            if (game.playerY > GroundY() - PLAYER_RADIUS) {
                game.playerY = GroundY() - PLAYER_RADIUS;
                game.playerVelocityY = 0.0f;
            }

            game.enemy.x -= game.enemy.speed * dt;
            if (!game.enemy.passed && game.enemy.x + ENEMY_WIDTH < PLAYER_X - PLAYER_RADIUS) {
                game.enemy.passed = true;
                game.score++;
            }
            if (game.enemy.x + ENEMY_WIDTH < 0.0f) {
                ResetEnemy(&game.enemy, game.score);
            }

            Rectangle enemyRect = GetEnemyRect(&game.enemy);
            Vector2 playerCenter = { PLAYER_X, game.playerY };
            if (CheckCollisionCircleRec(playerCenter, PLAYER_RADIUS, enemyRect)) {
                game.gameOver = true;
            }
        }

        BeginDrawing();
        DrawGame(&game);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
