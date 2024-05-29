#ifndef WELT_DRAW_H
#define WELT_DRAW_H

#include <raylib/raylib.h>

void DrawCubeTexture(Texture2D texture, Vector3 position, float width, float height, float length, Color color);
void DrawCubeAroundVector(Texture2D texture, Vector3 start, Vector3 v, float width, float length, Color color);

#endif