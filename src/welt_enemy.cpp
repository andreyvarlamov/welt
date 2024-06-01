#include "welt_enemy.h"

#include <raylib/raymath.h>
#include <raylib/raylib.h>

#include "welt_draw.h"
#include "welt_settings.h"

void DrawEnemy(Texture2D texture, Vector3 position)
{
    float headHeight = 0.4f;
    float neckLength = headHeight * 0.3f;
    float shoulderLength = headHeight;
    float armLength = headHeight * 1.5f;
    float handLength = headHeight * 1.1f;
    float wristLength = headHeight * 0.6f;
    float torsoLength = headHeight * 2.2f;
    float hipLength = headHeight * 0.5f;
    float thighLength = headHeight * 1.5f;
    float shinLength = headHeight * 1.9f;

    float height = headHeight + neckLength + torsoLength + thighLength + shinLength;
    float eyeHeight = height - 0.4f * headHeight;
    printf("eyeHeight = %f", eyeHeight);

#if (DRAW_ENEMY_MESH == 0)
    float radius = 0.5f;
    Vector3 start = {position.x, position.y + radius, position.z};
    Vector3 end = {position.x, position.y + height - radius, position.z};
    DrawCapsuleWithNormals(start, end, radius, 21, 9, RED);
#else
    Color c = GRAY;

    // head
    Vector3 headTop = {position.x, position.y + height, position.z};
    Vector3 headBot = {headTop.x, headTop.y - headHeight, headTop.z};
    DrawLine3D(headBot, headTop, c);

    // torso
    Vector3 torsoTop = headBot;
    Vector3 torsoBot = {torsoTop.x, torsoTop.y - torsoLength, torsoTop.z};
    DrawLine3D(torsoBot, torsoTop, c);

    // shoulders
    Vector3 shoulderStart = torsoTop;
    Vector3 aShoulderEnd = {shoulderStart.x + shoulderLength, shoulderStart.y, shoulderStart.z};
    DrawLine3D(shoulderStart, aShoulderEnd, c);
    Vector3 bShoulderEnd = {shoulderStart.x - shoulderLength, shoulderStart.y, shoulderStart.z};
    DrawLine3D(shoulderStart, bShoulderEnd, c);

    // arms
    Vector3 aArmStart = aShoulderEnd;
    Vector3 aArm = {0.0f, -armLength, 0.0f};
    Vector3 aArmEnd = Vector3Add(aArmStart, aArm);
    DrawLine3D(aArmStart, aArmEnd, c);
    Vector3 bArmStart = bShoulderEnd;
    Vector3 bArm = {-aArm.x, aArm.y, aArm.z};
    Vector3 bArmEnd = Vector3Add(bArmStart, bArm);
    DrawLine3D(bArmStart, bArmEnd, c);

    // hands
    Vector3 aHandStart = aArmEnd;
    Vector3 aHand = {0.0f, -handLength, 0.0f};
    Vector3 aHandEnd = Vector3Add(aHandStart, aHand);
    DrawLine3D(aHandStart, aHandEnd, c);
    Vector3 bHandStart = bArmEnd;
    Vector3 bHand = {-aHand.x, aHand.y, aHand.z};
    Vector3 bHandEnd = Vector3Add(bHandStart, bHand);
    DrawLine3D(bHandStart, bHandEnd, c);

    // wrists
    Vector3 aWristStart = aHandEnd;
    Vector3 aWrist = {0.0f, -wristLength, 0.0f};
    Vector3 aWristEnd = Vector3Add(aWristStart, aWrist);
    DrawLine3D(aWristStart, aWristEnd, c);
    Vector3 bWristStart = bHandEnd;
    Vector3 bWrist = {-aWrist.x, aWrist.y, aWrist.z};
    Vector3 bWristEnd = Vector3Add(bWristStart, bWrist);
    DrawLine3D(bWristStart, bWristEnd, c);

    // hips
    Vector3 hipStart = torsoBot;
    Vector3 aHipEnd = {hipStart.x + hipLength, hipStart.y, hipStart.z};
    DrawLine3D(hipStart, aHipEnd, c);
    Vector3 bHipEnd = {hipStart.x - hipLength, hipStart.y, hipStart.z};
    DrawLine3D(hipStart, bHipEnd, c);

    // thighs
    Vector3 aThighStart = aHipEnd;
    Vector3 aThigh = {0.0f, -thighLength, 0.0f};
    Vector3 aThighEnd = Vector3Add(aThighStart, aThigh);
    DrawLine3D(aThighStart, aThighEnd, c);
    Vector3 bThighStart = bHipEnd;
    Vector3 bThigh = {-aThigh.x, aThigh.y, aThigh.z};
    Vector3 bThighEnd = Vector3Add(bThighStart, bThigh);
    DrawLine3D(bThighStart, bThighEnd, c);

    // shins
    Vector3 aShinStart = aThighEnd;
    Vector3 aShin = {0.0f, -shinLength, 0.0f};
    Vector3 aShinEnd = Vector3Add(aShinStart, aShin);
    DrawLine3D(aShinStart, aShinEnd, c);
    Vector3 bShinStart = bThighEnd;
    Vector3 bShin = {-aShin.x, aShin.y, aShin.z};
    Vector3 bShinEnd = Vector3Add(bShinStart, bShin);
    DrawLine3D(bShinStart, bShinEnd, c);
#endif
}