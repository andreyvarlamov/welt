#include "welt_enemy.h"

#include <raylib/raymath.h>
#include <raylib/raylib.h>

#include "welt_draw.h"
#include "welt_settings.h"

void DrawEnemy(Texture2D texture, Vector3 position)
{
    float height = 2.0f;
    float radius = 0.5f;

#if (DRAW_ENEMY_MESH == 0)
    Vector3 start = {position.x, position.y + radius, position.z};
    Vector3 end = {position.x, position.y + height - radius, position.z};
    DrawCapsuleWithNormals(start, end, radius, 21, 9, RED);
#else
    Vector3 p;
    Color c = GRAY;

    // torso
    float torsoProportionStart = height * 0.5f;
    float torsoProportionEnd = height * 0.85f;
    float torsoWidth = height * 0.3f;
    float torsoHeight = torsoProportionEnd - torsoProportionStart;
    float torsoDepth = height * 0.1f;
    p = {position.x, position.y + (torsoProportionStart + torsoProportionEnd) * 0.5f, position.z};
    DrawCubeTexture(texture, p, torsoWidth, torsoHeight, torsoDepth, c);

    // head
    float headStart = torsoProportionEnd;
    float headEnd = height;
    float headHeight = headEnd - headStart;
    float headRadius = headHeight * 0.5f;
    p = {position.x, position.y + headStart + headRadius, position.z};
    DrawSphereWithNormals(p, headRadius, 6, 6, c);
#endif

    // DrawLine3D(start, end, RED);

    // DrawSphereWithNormals(end, 1.0f, 6, 6, RED);
}