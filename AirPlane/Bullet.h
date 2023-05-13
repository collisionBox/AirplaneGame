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
        VECTOR pos;// 位置ベクトル.
        VECTOR prePos;// 予想位置ベクトル.
        VECTOR dir;// 方向ベクトル.
        bool aliveFlag;// 生きているかどうか.
        int mh;// モデルハンドル.
        VECTOR velocity;// 弾速ベクトル.

    }bullet[20];
    ObjectTag myTag;
    const float MaxBulletNum = 20;// 弾の同時処理最大数.
    const float ColRadius = 10.0f;// 当たり判定半径.
    const float BarrelHead = 85.0f;// 砲身先端.
    const float Speed = 800.0f;// 弾速.
};

