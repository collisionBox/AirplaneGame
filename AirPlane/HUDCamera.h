#pragma once
#include "CameraBase.h"
class HUDCamera :
    public CameraBase
{
public: 
    HUDCamera();
    ~HUDCamera();
    void Init(VECTOR pos, MATRIX matRot);
    void Update(VECTOR pos, MATRIX matRot, float deltaTime);
private:
    const float OffsetLen = 20.0f;
    const float OffsetY = 5.0f;
};

