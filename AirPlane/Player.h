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
    
    const float AirDensity = 1.293f;// ��C���x.
    const float G = 9.80665f;// �d�͉����x(m/s^2).

    // F-15���Q�l�i�\�[�XURL�Fhttp://www.masdf.com/eagle/spec.html �j.
    const float Mass = 13000.0f;// ����(kg).
    const float SpeedMax = 850.0f;
    const float WingArea = 56.5f;
};

