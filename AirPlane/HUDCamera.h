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
    const VECTOR cockpit = VGet(0.0f, 18.708f, -92.272f);
    const VECTOR Cockpit = VGet(0.0f, 23.708f, -92.272f);
};

