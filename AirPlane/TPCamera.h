#pragma once
#include "CameraBase.h"
class TPCamera :
    public CameraBase
{
public:
    void Init(VECTOR pos, MATRIX matRot, const int modelHandle, const int frameIndex)override;
    void Update(VECTOR pos, MATRIX matRot)override;
    void Draw(VECTOR pos, MATRIX matRot, VECTOR velocity)override;
    void DebagDraw()override;
private:
    const float OffsetLen = 180.0f;
    const float OffsetY = 120.0f;
    const float OffsetX = sqrtf(OffsetLen * OffsetLen - OffsetY * OffsetY);

};

