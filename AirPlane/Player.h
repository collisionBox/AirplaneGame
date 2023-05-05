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

    VECTOR velocity; // ë¨ìx[m/s].
    VECTOR dirAdd;
    VECTOR zAxsisDir;
    const float UpwardAccel = 8.0f;
    const float DefaultUpwardAccel = 5.0f;
    const float DownwardAccel = 8.0f;
    const float DefaultDownwardAccel = 5.0f;
    const float MaxUpVec = 100.0f;
    const float MaxPower = 100.0f;
    const float Gravity = 9.80665f;
    const VECTOR InitDir = VGet(0.0f, 0.0f, -1.0f);
    const float MaxSpeed = 40.0f;
    const float DefaultDownwardSpeed = -10.0f;// é©ëRç~â∫ë¨ìx.
    VECTOR rotate;

    MATRIX mat;
    MATRIX matRot;
    MATRIX matTrans;
    float yaw, pitch, roll;
    VECTOR xAxis, yAxis, zAxis;
    QUATERNION quat;
    const float ModelScale = 0.015f;
    const float YawSpeed     = 10.0f;
    const float PitchSpeed   = 10.0f;
    const float RollSpeed    = 10.0f;
    MATRIX matVelocity;
};

