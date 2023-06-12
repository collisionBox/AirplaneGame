#pragma once
#include "CameraBase.h"
class HUDCamera :
    public CameraBase
{
public: 
    void Init(VECTOR pos, MATRIX matRot, const int modelHandle, const int frameIndex)override;
    void Update(VECTOR pos, MATRIX matRot)override;
    void Draw(VECTOR pos, MATRIX matRot)override;
    void UI(VECTOR pos, MATRIX matRot);
    void SwivelMeter(VECTOR pos, MATRIX matRot);
    void DebagDraw()override;
private:
    const float OffsetLen = 10.0f;
    const float OffsetY = 50.0f;
    const float AjustY = 7.85f;// êlä‘ÇÃéãäEÇÃçÇÇ≥Ç…Ç∑ÇÈ.
    int ModelHandle;
    int FrameIndex;
    const float SwivelMeterLineLen = 50.0f;
    const int Green = GetColor(0, 255, 0);
};

