#include "welt.h"

#include <cstdio>

#include <raylib/raylib.h>

#include "welt_util.h"
#include "welt_draw.h"
#include "welt_player.h"
#include "welt_settings.h"

int main(int argc, char **argv)
{
    InitWindow(1920, 1080, "Hello world");

    Texture2D texture = LoadTexture(TEXTURE_PATH);

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

                DrawWorld(texture, 0.0f, worldDim, worldDim);
            EndMode3D();

            DrawFPS(10, 10);

            DrawPlayerDebugInfo(&playerState);
        EndDrawing();
    }

    UnloadTexture(texture);

    CloseWindow();

    return 0;
}

#include "welt_draw.cpp"
#include "welt_player.cpp"