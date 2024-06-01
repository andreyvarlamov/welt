#include "welt_player.h"

#include <raylib/raylib.h>
#include <raylib/raymath.h>

#include "welt_settings.h"

PlayerState MakePlayer(Vector3 pos, Vector3 targetDir, float fov, float cameraHeight, float speed)
{
    Camera camera = {};
    camera.position = {pos.x, pos.y + cameraHeight, pos.z};
    camera.target = Vector3Add(camera.position, targetDir);
    camera.up = {0.0f, 1.0f, 0.0f};
    camera.fovy = fov;
    camera.projection = CAMERA_PERSPECTIVE;

    PlayerState playerState = {};
    playerState.camera = camera;
    playerState.cameraHeight = cameraHeight;
    playerState.speed = speed;

    return playerState;
}

void movePlayer(PlayerState *playerState, Vector3 dP)
{
    playerState->camera.position = Vector3Add(playerState->camera.position, dP);
    playerState->camera.target = Vector3Add(playerState->camera.target, dP);
}

void applyYVelocity(PlayerState *playerState, float delta)
{
        float dY = playerState->yVelocity * delta;

        Vector3 dP = {0.0f, dY, 0.0f};

        movePlayer(playerState, dP);

        // TODO: Fix bug with some kind of feedback loop between camera height and onGround calculation
        Vector3 currentP = GetPlayerPosition(playerState);
        if (currentP.y <= 0.0f)
        {
            SetPlayerPosition(playerState, {currentP.x, 0.0f, currentP.z});
            playerState->onGround = true;
        }
        else
        {
            playerState->onGround = false;
        }

}

void updatePlayerPhysics(PlayerState *playerState, float delta, bool ignoreGravity, bool shouldJump)
{
#if (ENABLE_GRAVITY == 0)
    playerState->yVelocity = 0.0f;
    playerState->onGround = false;
#else
    if (ignoreGravity)
    {
        playerState->yVelocity = 0.0f;
        playerState->onGround = false;
    }
    else if (shouldJump && playerState->onGround)
    {
        float jumpVel = JUMP_VEL;
        playerState->yVelocity = jumpVel;
        applyYVelocity(playerState, delta);
    }
    else
    {
        float yAcceleration = -GRAVITY;
        playerState->yVelocity += yAcceleration * delta;
        applyYVelocity(playerState, delta);
    }
#endif
}

struct PlayerInput
{
    Vector3 rotation;
    Vector3 movement;
    bool jump;
    bool isMovingVertically;
};

PlayerInput getPlayerInput(PlayerState *playerState)
{
    Vector2 mouseDelta = GetMouseDelta();

    Vector3 reqRotation = {};

    reqRotation.x = mouseDelta.x * MOUSE_SENS;
    reqRotation.y = mouseDelta.y * MOUSE_SENS;

    Vector3 reqMovement  = {};

    if (IsKeyDown(KEY_W)) reqMovement.x += 1.0f;
    if (IsKeyDown(KEY_S)) reqMovement.x -= 1.0f;
    if (IsKeyDown(KEY_A)) reqMovement.y -= 1.0f;
    if (IsKeyDown(KEY_D)) reqMovement.y += 1.0f;

    reqMovement = Vector3Normalize(reqMovement);

    bool isMovingVertically = false;
    bool shouldJump = false;
    bool isDucking = false;
#if (ENABLE_FLIGHT == 1)
    if (IsKeyDown(KEY_LEFT_SHIFT))
    {
        reqMovement.z -= 1.0f;
        isMovingVertically = true;
    }
    if (IsKeyDown(KEY_SPACE)) 
    {
        reqMovement.z += 1.0f;
        isMovingVertically = true;
    }

    reqMovement.z *= playerState->speed;
#else
    if (IsKeyDown(KEY_SPACE))
    {
        shouldJump = true;
    }

    if (IsKeyDown(KEY_LEFT_SHIFT))
    {
        playerState->cameraHeight = PLAYER_DUCK_HEIGHT;
        isDucking = true;
    }
    else
    {
        playerState->cameraHeight = PLAYER_CAMERA_HEIGHT;
    }
#endif

    float speed = (playerState->onGround && !isDucking) ? playerState->speed : playerState->speed * 0.4f;
    reqMovement = Vector3Scale(reqMovement, speed);

    PlayerInput result = {};
    result.rotation = reqRotation;
    result.movement = reqMovement;
    result.jump = shouldJump;
    result.isMovingVertically = isMovingVertically;
    return result;
}

void UpdatePlayer(PlayerState *playerState, float delta)
{
    PlayerInput input = getPlayerInput(playerState);

    UpdateCameraPro(&playerState->camera, Vector3Scale(input.movement, delta), input.rotation, 0.0f);

    updatePlayerPhysics(playerState, delta, input.isMovingVertically, input.jump);
}

void SetPlayerPosition(PlayerState *playerState, Vector3 pos)
{
    Vector3 newCameraP = {pos.x, pos.y + playerState->cameraHeight, pos.z};
    Vector3 dP = Vector3Subtract(newCameraP, playerState->camera.position);
    movePlayer(playerState, dP);
}

Vector3 GetPlayerPosition(PlayerState *playerState)
{
    Vector3 p = playerState->camera.position;
    Vector3 result = {p.x, p.y - playerState->cameraHeight, p.z};
    return result;
}

void DrawPlayerDebugInfo(PlayerState *playerState)
{
    DrawText(TextFormat("ON GROUND: %d", playerState->onGround), 10, 30, 20, MAROON);
    Vector3 p = GetPlayerPosition(playerState);
    DrawText(TextFormat("P: {%.4f, %.4f, %.4f}", p.x, p.y, p.z), 10, 50, 20, MAROON);
}