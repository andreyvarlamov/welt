#ifndef WELT_PLAYER_H
#define WELT_PLAYER_H

#include <raylib/raylib.h>

struct PlayerState
{
    Camera camera;
    float cameraHeight;

    float speed;

    float yVelocity;

    bool onGround;
};

PlayerState MakePlayer(Vector3 pos, Vector3 target, float fov, float cameraHeight, float speed);

void UpdatePlayer(PlayerState *playerState, float delta);

void SetPlayerPosition(PlayerState *playerState, Vector3 pos);
Vector3 GetPlayerPosition(PlayerState *playerState);

void DrawPlayerDebugInfo(PlayerState *playerState);

#endif