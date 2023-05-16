#pragma once
#include "ObjectBase.h"


class Bullet :
    public ObjectBase
{
public:
    Bullet(ObjectTag userTag);
    Bullet(VECTOR pos, VECTOR dir, ObjectTag userTag);
    ~Bullet();
    void Init(VECTOR pos, VECTOR dir);
    void Update(float deltaTime);
    void Generate(VECTOR pos, VECTOR dir);
    void OnCollisionEnter(const ObjectBase* other) override;
    void Draw();


private:
    ObjectTag myTag;
    VECTOR velocity;
    const float ColRadius = 10.0f;// ìñÇΩÇËîªíËîºåa.
    const float BarrelHead = 85.0f;// ñCêgêÊí[.
    const float Speed = 800.0f;// íeë¨.
};

