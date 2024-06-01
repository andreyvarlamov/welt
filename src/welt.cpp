#include "welt.h"

#include <cstdio>

#include <raylib/raylib.h>

#define RLIGHTS_IMPLEMENTATION
#include <raylib/rlights.h>

#include "welt_util.h"
#include "welt_settings.h"
#include "welt_draw.h"
#include "welt_world.h"
#include "welt_player.h"
#include "welt_enemy.h"

int main(int argc, char **argv)
{
    InitWindow(1920, 1080, "WELT");

    Texture2D grassTexture = LoadTexture("res/textures/grass.png");
    Texture2D whiteTexture = LoadTexture("res/textures/white.png");

    float fps = FPS;
    float delta = 1.0f/fps;

    SetTargetFPS(fps);

    DisableCursor();

    int worldDim = 16;

    PlayerState playerState = MakePlayer({0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, PLAYER_FOV, PLAYER_CAMERA_HEIGHT, PLAYER_SPEED);

    Shader shader = LoadShader("res/shaders/lighting.vs", "res/shaders/lighting.fs");
    shader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(shader, "viewPos");

    int ambientLoc = GetShaderLocation(shader, "ambient");
    SetShaderValue(shader, ambientLoc, (float[4]){0.1f, 0.1f, 0.1f, 0.1f}, SHADER_UNIFORM_VEC4);

    Light light = CreateLight(LIGHT_DIRECTIONAL, {0.0f, 10.0f, -10.0f}, {0.0f, 0.0f, 0.0f}, YELLOW, shader);

    while (!WindowShouldClose())
    {
        UpdatePlayer(&playerState, delta);

        BeginDrawing();
            ClearBackground(RAYWHITE);

            BeginMode3D(playerState.camera);
                // DrawGrid(worldDim * 2 + 4, 0.5f);

                BeginShaderMode(shader);
                    DrawWorld(grassTexture, 0.0f, worldDim, worldDim);

                    DrawEnemy(whiteTexture, {0.0f, 0.0f, 2.0f});
                EndShaderMode();
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