#pragma once
#include "ObjectBase.h"
class PlayerCamera :
    public ObjectBase
{
public:
    PlayerCamera();
    ~PlayerCamera() {};
    void Init();
    void Update(float deltaTime)override;
    void Input(float deltaTime);
    void Draw();
private:
    float acceleration;// �A�N�Z���ɒǉ���������x.
    float accel;
    const float InitAccel = 30.0f;
    VECTOR velosity;
    VECTOR aimPos;// �����_�ڕW.
    float roll;// x
    float radianInclement;
    const float DefaultLength = 800.0f;
    float length;

    float pichi;// y
    float yow;// z
    const float PichiUp = 3.0f;
};

