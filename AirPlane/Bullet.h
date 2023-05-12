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
    void OnCollisionEnter(const ObjectBase* other) override;
    void Draw();


private:
    bool reflectionFlag;// 一度反射しているかどうか.
    VECTOR velocity;// 弾速ベクトル.
    ObjectTag myTag;
    const float colRadius = 10.0f;// 当たり判定半径.
    const float barrelHead = 85.0f;// 砲身先端.
    const float speed = 800.0f;// 弾速.

};

