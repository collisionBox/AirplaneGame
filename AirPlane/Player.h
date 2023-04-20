#pragma once
#include "ObjectBase.h"
class Player :
    public ObjectBase
{public:
    Player();
    ~Player();
    void Init();
    void Update(float deltaTime)override;
    void Draw()override;
    void OnCollisionEnter(const ObjectBase* other);
private:

    VECTOR velocity; // 速度[m/s].
    VECTOR dirAdd;
    const float YowSpeed = 2.0f;
    const float UpwardAccel = 8.0f;
    const float DefaultUpwardAccel = 5.0f;
    const float DownwardAccel = 8.0f;
    const float DefaultDownwardAccel = 5.0f;
    const float MaxUpVec = 100.0f;
    const float MaxPower = 100.0f;
    const float Gravity = 9.80665f;
    const VECTOR InitDir = VGet(0.0f, 1.0f, 0.0f);
    const float MaxSpeed = 40.0f;
    const float DefaultDownwardSpeed = -10.0f;// 自然降下速度.
};

