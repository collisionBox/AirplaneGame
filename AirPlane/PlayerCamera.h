#pragma once
#include "ObjectBase.h"
class PlayerCamera :
    public ObjectBase
{
public:
    PlayerCamera();
    ~PlayerCamera();
    void Update(float deltaTime)override;

private:
    VECTOR targetPos;
    const float len = 100.0f;
};

