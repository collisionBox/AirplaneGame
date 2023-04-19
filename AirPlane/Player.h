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

    VECTOR velocity; // ‘¬“x[m/s].
    VECTOR acceleration; // ‰Á‘¬“x[m/s^2].
    VECTOR orientation; // ‰ñ“][rad].
    float upVec;
    float power;
    float rotateSpeed;
    const float MaxUpVec = 100.0f;
    const float MaxPower = 100.0f;
    const VECTOR InitDir = VGet(0.0f, 1.0f, 0.0f);
};

