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
    float CalculateLift();
    float CalculataAoA();
    float CalculateCL();
    VECTOR velocity;
    
    const float AirDensity = 1.293f;// 空気密度.
    const float G = 9.80665f;// 重力加速度(m/s^2).

    // F-15を参考（ソースURL：http://www.masdf.com/eagle/spec.html ）.
    const float Mass = 13000.0f;// 質量(kg).
    const float SpeedMax = 850.0f;
    const float WingArea = 56.5f;
};

