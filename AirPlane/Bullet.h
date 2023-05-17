#pragma once
#include "ObjectBase.h"


class Bullet :
    public ObjectBase
{
public:
    Bullet(ObjectTag userTag);
    ~Bullet();
    void Init(VECTOR pos, VECTOR dir);
    void Update(float deltaTime);
    void Generate(VECTOR pos, VECTOR dir);
    void MakePermitUpdateFalse() { permitUpdate = false; }// permitUpdate��false�ɂ���.
    void OnCollisionEnter(const ObjectBase* other) override;
    void Draw();


private:
    ObjectTag myTag;
    VECTOR velocity;
    const float ColRadius = 0.1f;// �����蔻�蔼�a.
    const float BarrelHead = 85.0f;// �C�g��[.
    const float Speed = 8.0f;// �e��.
    const float DeadTime = 3.0f;
    float timeCount;
};

