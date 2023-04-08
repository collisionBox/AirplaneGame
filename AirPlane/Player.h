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
    float CalculateAoA();
    float CalculateCL();
    float CalculataCD();
    VECTOR CalculateLiftVec();
    float CalculateLiftOrDrag(float coefficient, float surface, float velocity, float airDensity = 1.293f);

    VECTOR velocity; // 速度[m/s].
    VECTOR acceleration; // 加速度[m/s^2].
    VECTOR orientation; // 回転[rad].
    float upVec;
    float power;
    float rotateSpeed;
    const VECTOR Gravity = VGet(0.0f, -G * Mass, 0.0f);
    const float AirDensity = 1.293f;// 空気密度.
    const float G = 9.80665f;// 重力加速度(m/s^2).
    const float Mass = 10400.0f;// 質量(kg).

    const float SpeedMax = 850.0f;
    const float BradeArea = 10.0f;// ブレード面積.
    const float BradeRadius = 14.6f;// ブレード半径.
    const float RotorArra = BradeRadius * BradeRadius * DX_PI_F;
    const float RotateSpeedMax = 500.0f;// 最大回転数.
    const float RotateSpeedAccel = 10.0f;// 回転数の加速度.
    const float RotateSpeedDecel = 20.0f;// 回転数の減速度.
    const float BradePichi = 10.0f;// ブレードのピッチ角.
    const float EnginPower = 1301000.0f;// エンジン出力. 

    const float liftCoefficient = 1.2;  // 揚力係数
    const float dragCoefficient = 0.02;  // 抗力係数
    const float rotorForce = 2000.0;  // ローターの力[N]
    const float rotorTorque = 500.0;  // ローターのトルク[Nm]
    const float momentOfInertia = 2000.0;  // 慣性モーメント[Nm^2]
};

