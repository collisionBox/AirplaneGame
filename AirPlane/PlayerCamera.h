#pragma once
#include "ObjectBase.h"
class PlayerCamera :
    public ObjectBase
{
public:
    PlayerCamera();
    ~PlayerCamera() {};
    void Init();
    void Update(float deltaTime);
    void Input(float deltaTime);
    void Draw();
private:
    float acceleration;// �A�N�Z���ɒǉ���������x.
    float accel;
    const float InitAccel = 30.0f;
    VECTOR velosity;
    VECTOR aimPos;// �����_�ڕW.
    VECTOR prePos;// �\���|�W�V����.
    float roll;
    float rollInclement;
    const float DefaultLength = 50.0f;
    float length;
};

