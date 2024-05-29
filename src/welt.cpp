#include "welt.h"

#include <cstdio>

#include <raylib/raylib.h>

#include "welt_util.h"
#include "welt_settings.h"
#include "welt_draw.h"
#include "welt_world.h"
#include "welt_player.h"
#include "welt_enemy.h"

int main(int argc, char **argv)
{
    InitWindow(1920, 1080, "WELT");

    Texture2D grassTexture = LoadTexture(GRASS_TEXTURE);
    Texture2D whiteTexture = LoadTexture(WHITE_TEXTURE);

    float fps = FPS;
    float delta = 1.0f/fps;

    SetTargetFPS(fps);

    DisableCursor();

    int worldDim = 16;

    PlayerState playerState = MakePlayer({0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, PLAYER_FOV, PLAYER_CAMERA_HEIGHT, PLAYER_SPEED);

    while (!WindowShouldClose())
    {
        UpdatePlayer(&playerState, delta);

        BeginDrawing();
            ClearBackground(RAYWHITE);

            BeginMode3D(playerState.camera);
                DrawGrid(worldDim * 2 + 4, 0.5f);

                DrawWorld(grassTexture, 0.0f, worldDim, worldDim);

                DrawEnemy(whiteTexture, {0.0f, 0.0f, 2.0f});
            EndMode3D();

            DrawFPS(10, 10);

            DrawPlayerDebugInfo(&playerState);
        EndDrawing();
    }

    UnloadTexture(grassTexture);
    UnloadTexture(whiteTexture);

    CloseWindow();

    return 0;
}

#include "welt_draw.cpp"
#include "welt_world.cpp"
#include "welt_player.cpp"
#include "welt_enemy.cpp"