#include "welt_world.h"

#include "welt_util.h"

#include <raylib/raylib.h>

void DrawWorld(Texture2D texture, float yPos, int cols, int rows)
{
    Assert(cols % 2 == 0);
    Assert(rows % 2 == 0);

    float cubeDim = 1.0f;

    for (int row = -rows/2; row < rows/2; row++)
    {
        for (int col = -cols/2; col < cols/2; col++)
        {
            DrawCubeTexture(texture, {cubeDim/2 + (float) col, yPos - cubeDim/2, cubeDim/2 + (float) row}, cubeDim, cubeDim, cubeDim, WHITE);
        }
    }
}
