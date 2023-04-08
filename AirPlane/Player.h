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

    VECTOR velocity; // ���x[m/s].
    VECTOR acceleration; // �����x[m/s^2].
    VECTOR orientation; // ��][rad].
    float upVec;
    float power;
    float rotateSpeed;
    const VECTOR Gravity = VGet(0.0f, -G * Mass, 0.0f);
    const float AirDensity = 1.293f;// ��C���x.
    const float G = 9.80665f;// �d�͉����x(m/s^2).
    const float Mass = 10400.0f;// ����(kg).

    const float SpeedMax = 850.0f;
    const float BradeArea = 10.0f;// �u���[�h�ʐ�.
    const float BradeRadius = 14.6f;// �u���[�h���a.
    const float RotorArra = BradeRadius * BradeRadius * DX_PI_F;
    const float RotateSpeedMax = 500.0f;// �ő��]��.
    const float RotateSpeedAccel = 10.0f;// ��]���̉����x.
    const float RotateSpeedDecel = 20.0f;// ��]���̌����x.
    const float BradePichi = 10.0f;// �u���[�h�̃s�b�`�p.
    const float EnginPower = 1301000.0f;// �G���W���o��. 

    const float liftCoefficient = 1.2;  // �g�͌W��
    const float dragCoefficient = 0.02;  // �R�͌W��
    const float rotorForce = 2000.0;  // ���[�^�[�̗�[N]
    const float rotorTorque = 500.0;  // ���[�^�[�̃g���N[Nm]
    const float momentOfInertia = 2000.0;  // �������[�����g[Nm^2]
};

