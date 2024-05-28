#include <cstdio>

#include <raylib/raylib.h>

#include "welt_util.h"
#include "welt_draw.h"

#define TEXTURE_PATH "res/grass.png"

int main(int argc, char **argv)
{
    InitWindow(1920, 1080, "Hello world");

    Camera camera = {};
    camera.position = {0.0f, 10.0f, 10.0f};
    camera.target = {0.0f, 0.0f, 0.0f};
    camera.up = {0.0f, 1.0f, 0.0f};
    camera.fovy = 80.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    Texture2D texture = LoadTexture(TEXTURE_PATH);

    SetTargetFPS(60);

    DisableCursor();

    int worldDim = 16;

    while (!WindowShouldClose())
    {
        UpdateCamera(&camera, CAMERA_FREE);

        BeginDrawing();
            ClearBackground(RAYWHITE);

            BeginMode3D(camera);
                DrawGrid(worldDim * 2 + 4, 0.5f);

                DrawWorld(texture, 0.0f, worldDim, worldDim);
            EndMode3D();

            DrawFPS(10, 10);
        EndDrawing();
    }

    UnloadTexture(texture);

    CloseWindow();

    return 0;
}

#include "welt_draw.cpp"