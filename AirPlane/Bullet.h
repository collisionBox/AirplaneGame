#pragma once
#include "ObjectBase.h"


class Bullet :
    public ObjectBase
{
public:
    
    Bullet(ObjectTag tag);
    Bullet(VECTOR pos, VECTOR dir, ObjectTag userTag);
    ~Bullet();
    void Init(VECTOR pos, VECTOR dir);
    void Update(float deltaTime);
    void Generate(VECTOR pos, VECTOR dir);
    void OnCollisionEnter(const ObjectBase* other) override;
    void Draw();


private:
    struct BULLET
    {
        VECTOR pos;// �ʒu�x�N�g��.
        VECTOR prePos;// �\�z�ʒu�x�N�g��.
        VECTOR dir;// �����x�N�g��.
        bool aliveFlag;// �����Ă��邩�ǂ���.
        int mh;// ���f���n���h��.
        VECTOR velocity;// �e���x�N�g��.

    }bullet[20];
    ObjectTag myTag;
    const float MaxBulletNum = 20;// �e�̓��������ő吔.
    const float ColRadius = 10.0f;// �����蔻�蔼�a.
    const float BarrelHead = 85.0f;// �C�g��[.
    const float Speed = 800.0f;// �e��.
};

