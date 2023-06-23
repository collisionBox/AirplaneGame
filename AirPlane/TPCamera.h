#pragma once
#include "CameraBase.h"
#include "Math.h"
class TPCamera :
    public CameraBase
{
public:
    void Init(VECTOR pos, MATRIX matRot, const int modelHandle, const int frameIndex)override;
    void Update(VECTOR pos, MATRIX matRot, float deltaTime)override;
    void Draw(VECTOR pos, MATRIX matRot, VECTOR velocity)override;
    void DebagDraw()override;
private:
    VECTOR dir;
    VECTOR dirVelocity;
    const float OffsetLen = 200.0f;
    const float OffsetY = 120.0f;
    const float OffsetX = sqrtf(OffsetLen * OffsetLen - OffsetY * OffsetY);
    const float SpringStrength = 4.0f;
    const float OffsetAngle = ToRadian(40.0f);
    const float Epsilon = 0.01f;// åÎç∑ï‚ê≥.
    const float MaxAngle = 45;
    float valiable;
};

