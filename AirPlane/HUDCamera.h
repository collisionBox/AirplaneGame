#pragma once
#include "CameraBase.h"
class HUDCamera :
    public CameraBase
{
public: 
    void Init(VECTOR pos, MATRIX matRot, const int modelHandle, const int frameIndex)override;
    void Update(VECTOR pos, MATRIX matRot)override;
    void DebagDraw()override;
private:
    const float OffsetLen = 10.0f;
    const float OffsetY = 50.0f;
    const float AjustY = 7.85f;
    VECTOR cockpitPos;
    int ModelHandle;
    int FrameIndex;
};

