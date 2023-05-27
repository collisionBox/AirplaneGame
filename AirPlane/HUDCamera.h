#pragma once
#include "CameraBase.h"
class HUDCamera :
    public CameraBase
{
public: 
    HUDCamera();
    ~HUDCamera();
    void Init(VECTOR pos, MATRIX matRot);
    void Update(VECTOR pos, MATRIX matRot, float modelScale, float deltaTime);
private:
    const float OffsetLen = 200.0f;
    const float OffsetY = 50.0f;
    VECTOR cockpitPos;
};

