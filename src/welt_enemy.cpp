#include "welt_enemy.h"

#include <raylib/raymath.h>
#include <raylib/raylib.h>

#include "welt_draw.h"

void DrawEnemy(Texture2D texture, Vector3 position)
{
    float enemyHeight = 2.0f;

    Vector3 v = {0.0f, enemyHeight, 0.0f};
    DrawCubeAroundVector(texture, position, v, 0.75f, 0.5f, RED);

    Vector3 p = {0.75f, 1.7f, 0.0f};
    p = Vector3Add(p, position);
    v = {1.0f, -1.0f, 0.0f};
    // DrawCubeAroundVector(texture, p, v, 0.75f, 0.5f, YELLOW);
}