#pragma once
#include "ObjectBase.h"


class Bullet :
    public ObjectBase
{
public:
    Bullet(ObjectTag userTag);
    ~Bullet();
    void Init();// ������.
    void Update(float deltaTime)override;
    void Generate(VECTOR pos, MATRIX matDir);// ��������.
    const void MakePermitUpdateFalse() { permitUpdate = false; }// permitUpdate��false�ɂ���.
    void OnCollisionEnter(const ObjectBase* other) override;
    void Draw()override;


private:
    float CalculateAngle(VECTOR airplanePos, MATRIX airplaneMatDir);// �p�x���Z�o.
    void Delete();// ��������.
    ObjectTag myTag;
    VECTOR velocity;
    const float modelScale = 0.004f;
    const float ColRadius = 0.1f;// �����蔻�蔼�a.
    const float Speed = 1050.0f;// �e��.
    const float DeadTime = 3.0f;
    float timeCount;
    const VECTOR PosCorrectionScale = VGet(-1.2f, 0.0f, -5.0f);// �e���ʒu�␳�萔.
    const float GunTargetingDistance = 800.0f;
};

