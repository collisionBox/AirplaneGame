#pragma once
#include "CameraBase.h"
class HUDCamera :
    public CameraBase
{
public: 
    HUDCamera();
    ~HUDCamera();
    void Init();
    void Update(VECTOR pos, MATRIX matRot, float deltaTime);
private:
    const float OffsetLen = 30.0f;
    const float OffsetY = 20.0f;
};

