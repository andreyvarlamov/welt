#include "welt_draw.h"

#include <raylib/raylib.h>
#include <raylib/rlgl.h>

void DrawCubeTexture(Texture2D texture, Vector3 position, float width, float height, float length, Color color)
{
    float x = position.x;
    float y = position.y;
    float z = position.z;

    rlSetTexture(texture.id);
        rlBegin(RL_QUADS);
            rlColor4ub(color.r, color.g, color.b, color.a);

            rlNormal3f(0.0f, 0.0f, 1.0f);
            rlTexCoord2f(0.0f, 0.0f); rlVertex3f(x - width/2, y - height/2, z + length/2);
            rlTexCoord2f(1.0f, 0.0f); rlVertex3f(x + width/2, y - height/2, z + length/2);
            rlTexCoord2f(1.0f, 1.0f); rlVertex3f(x + width/2, y + height/2, z + length/2);
            rlTexCoord2f(0.0f, 1.0f); rlVertex3f(x - width/2, y + height/2, z + length/2);

            rlNormal3f(0.0f, 0.0f, -1.0f);
            rlTexCoord2f(0.0f, 0.0f); rlVertex3f(x - width/2, y - height/2, z - length/2);
            rlTexCoord2f(1.0f, 0.0f); rlVertex3f(x - width/2, y + height/2, z - length/2);
            rlTexCoord2f(1.0f, 1.0f); rlVertex3f(x + width/2, y + height/2, z - length/2);
            rlTexCoord2f(0.0f, 1.0f); rlVertex3f(x + width/2, y - height/2, z - length/2);

            rlNormal3f(0.0f, 1.0f, 0.0f);
            rlTexCoord2f(0.0f, 0.0f); rlVertex3f(x - width/2, y + height/2, z - length/2);
            rlTexCoord2f(1.0f, 0.0f); rlVertex3f(x - width/2, y + height/2, z + length/2);
            rlTexCoord2f(1.0f, 1.0f); rlVertex3f(x + width/2, y + height/2, z + length/2);
            rlTexCoord2f(0.0f, 1.0f); rlVertex3f(x + width/2, y + height/2, z - length/2);

            rlNormal3f(0.0f, -1.0f, 0.0f);
            rlTexCoord2f(0.0f, 0.0f); rlVertex3f(x - width/2, y - height/2, z - length/2);
            rlTexCoord2f(1.0f, 0.0f); rlVertex3f(x + width/2, y - height/2, z - length/2);
            rlTexCoord2f(1.0f, 1.0f); rlVertex3f(x + width/2, y - height/2, z + length/2);
            rlTexCoord2f(0.0f, 1.0f); rlVertex3f(x - width/2, y - height/2, z + length/2);

            rlNormal3f(1.0f, 0.0f, 0.0f);
            rlTexCoord2f(0.0f, 0.0f); rlVertex3f(x + width/2, y - height/2, z - length/2);
            rlTexCoord2f(1.0f, 0.0f); rlVertex3f(x + width/2, y + height/2, z - length/2);
            rlTexCoord2f(1.0f, 1.0f); rlVertex3f(x + width/2, y + height/2, z + length/2);
            rlTexCoord2f(0.0f, 1.0f); rlVertex3f(x + width/2, y - height/2, z + length/2);

            rlNormal3f(-1.0f, 0.0f, 0.0f);
            rlTexCoord2f(0.0f, 0.0f); rlVertex3f(x - width/2, y - height/2, z - length/2);
            rlTexCoord2f(1.0f, 0.0f); rlVertex3f(x - width/2, y - height/2, z + length/2);
            rlTexCoord2f(1.0f, 1.0f); rlVertex3f(x - width/2, y + height/2, z + length/2);
            rlTexCoord2f(0.0f, 1.0f); rlVertex3f(x - width/2, y + height/2, z - length/2);

        rlEnd();
    rlSetTexture(0);
}

void DrawCubeAroundVector(Texture2D texture, Vector3 start, Vector3 v, float width, float length, Color color)
{
    Vector3 up = {0.0f, 1.0f, 0.0f };
    Vector3 sideNormal = Vector3CrossProduct(up, v);
    sideNormal = Vector3Normalize(sideNormal);

    // TODO: HERE
    if (Vector3Length(sideNormal) < 0.01f)
    {
        sideNormal = {1.0f, 0.0f, 0.0f};
    }

    Vector3 frontNormal = Vector3CrossProduct(v, sideNormal);
    frontNormal = Vector3Normalize(frontNormal);

    Vector3 upNormal = Vector3Normalize(v);

    Vector3 sideVec = Vector3Scale(sideNormal, width);
    Vector3 frontVec = Vector3Scale(frontNormal, length);

    Vector3 negSideVec = Vector3Scale(sideNormal, width);
    Vector3 negFrontVec = Vector3Scale(frontNormal, length);

    Vector3 end = Vector3Add(start, v);

    Vector3 v0;
    Vector3 v1;
    Vector3 v2;
    Vector3 v3;

    rlSetTexture(texture.id);
        rlBegin(RL_QUADS);
            rlColor4ub(color.r, color.g, color.b, color.a);

            rlNormal3f(frontNormal.x, frontNormal.y, frontNormal.z);
            v0 = Vector3Add(Vector3Add(start, negSideVec), frontVec);
            v1 = Vector3Add(Vector3Add(start, sideVec), frontVec);
            v2 = Vector3Add(Vector3Add(end, sideVec), frontVec);
            v3 = Vector3Add(Vector3Add(end, negSideVec), frontVec);
            rlTexCoord2f(0.0f, 0.0f); rlVertex3f(v0.x, v0.y, v0.z);
            rlTexCoord2f(1.0f, 0.0f); rlVertex3f(v1.x, v1.y, v1.z);
            rlTexCoord2f(1.0f, 1.0f); rlVertex3f(v2.x, v2.y, v2.z);
            rlTexCoord2f(0.0f, 1.0f); rlVertex3f(v3.x, v3.y, v3.z);

            rlNormal3f(-frontNormal.x, -frontNormal.y, -frontNormal.z);
            v0 = Vector3Add(Vector3Add(start, sideVec), negFrontVec);
            v1 = Vector3Add(Vector3Add(start, negSideVec), negFrontVec);
            v2 = Vector3Add(Vector3Add(end, negSideVec), negFrontVec);
            v3 = Vector3Add(Vector3Add(end, sideVec), negFrontVec);
            rlTexCoord2f(0.0f, 0.0f); rlVertex3f(v0.x, v0.y, v0.z);
            rlTexCoord2f(1.0f, 0.0f); rlVertex3f(v1.x, v1.y, v1.z);
            rlTexCoord2f(1.0f, 1.0f); rlVertex3f(v2.x, v2.y, v2.z);
            rlTexCoord2f(0.0f, 1.0f); rlVertex3f(v3.x, v3.y, v3.z);

            rlNormal3f(upNormal.x, upNormal.y, upNormal.z);
            v0 = Vector3Add(Vector3Add(start, sideVec), frontVec);
            v1 = Vector3Add(Vector3Add(start, negSideVec), frontVec);
            v2 = Vector3Add(Vector3Add(start, negSideVec), negFrontVec);
            v3 = Vector3Add(Vector3Add(start, sideVec), negFrontVec);
            rlTexCoord2f(0.0f, 0.0f); rlVertex3f(v0.x, v0.y, v0.z);
            rlTexCoord2f(1.0f, 0.0f); rlVertex3f(v1.x, v1.y, v1.z);
            rlTexCoord2f(1.0f, 1.0f); rlVertex3f(v2.x, v2.y, v2.z);
            rlTexCoord2f(0.0f, 1.0f); rlVertex3f(v3.x, v3.y, v3.z);

            rlNormal3f(-upNormal.x, -upNormal.y, -upNormal.z);
            v0 = Vector3Add(Vector3Add(end, negSideVec), negFrontVec);
            v1 = Vector3Add(Vector3Add(end, sideVec), negFrontVec);
            v2 = Vector3Add(Vector3Add(end, sideVec), frontVec);
            v3 = Vector3Add(Vector3Add(end, negSideVec), frontVec);
            rlTexCoord2f(0.0f, 0.0f); rlVertex3f(v0.x, v0.y, v0.z);
            rlTexCoord2f(1.0f, 0.0f); rlVertex3f(v1.x, v1.y, v1.z);
            rlTexCoord2f(1.0f, 1.0f); rlVertex3f(v2.x, v2.y, v2.z);
            rlTexCoord2f(0.0f, 1.0f); rlVertex3f(v3.x, v3.y, v3.z);

            rlNormal3f(sideNormal.x, sideNormal.y, sideNormal.z);
            v0 = Vector3Add(Vector3Add(start, sideVec), frontVec);
            v1 = Vector3Add(Vector3Add(end, sideVec), frontVec);
            v2 = Vector3Add(Vector3Add(end, sideVec), negFrontVec);
            v3 = Vector3Add(Vector3Add(start, sideVec), negFrontVec);
            rlTexCoord2f(0.0f, 0.0f); rlVertex3f(v0.x, v0.y, v0.z);
            rlTexCoord2f(1.0f, 0.0f); rlVertex3f(v1.x, v1.y, v1.z);
            rlTexCoord2f(1.0f, 1.0f); rlVertex3f(v2.x, v2.y, v2.z);
            rlTexCoord2f(0.0f, 1.0f); rlVertex3f(v3.x, v3.y, v3.z);

            rlNormal3f(-sideNormal.x, -sideNormal.y, -sideNormal.z);
            v0 = Vector3Add(Vector3Add(start, negSideVec), negFrontVec);
            v1 = Vector3Add(Vector3Add(end, negSideVec), negFrontVec);
            v2 = Vector3Add(Vector3Add(end, negSideVec), frontVec);
            v3 = Vector3Add(Vector3Add(start, negSideVec), frontVec);
            rlTexCoord2f(0.0f, 0.0f); rlVertex3f(v0.x, v0.y, v0.z);
            rlTexCoord2f(1.0f, 0.0f); rlVertex3f(v1.x, v1.y, v1.z);
            rlTexCoord2f(1.0f, 1.0f); rlVertex3f(v2.x, v2.y, v2.z);
            rlTexCoord2f(0.0f, 1.0f); rlVertex3f(v3.x, v3.y, v3.z);
        rlEnd();
    rlSetTexture(0);
}