#ifndef WELT_DRAW_H
#define WELT_DRAW_H

#include <raylib/raylib.h>

void DrawWorld(Texture2D texture, float yPos, int cols, int rows);
void DrawCubeTexture(Texture2D texture, Vector3 position, float width, float height, float length, Color color);

#endif