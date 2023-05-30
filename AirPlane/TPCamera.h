#pragma once
#include "CameraBase.h"
class TPCamera :
    public CameraBase
{
public:
    void Init(VECTOR pos, MATRIX matRot, const int modelHandle, const int frameIndex)override;
    void Update(VECTOR pos, MATRIX matRot, float deltaTime)override;
    void DebagDraw()override;
private:
    const float OffsetLen = 200.0f;
    const float OffsetY = 100.0f;
    const float OffsetX = OffsetLen * OffsetLen - OffsetY * OffsetY;
};

