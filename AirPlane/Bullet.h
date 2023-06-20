#pragma once
#include "ObjectBase.h"

class Bullet :
    public ObjectBase
{
public:

    Bullet(ObjectTag userTag);
    ~Bullet();
    void Init();// 初期化.
    void Update(float deltaTime)override;
    void Generate(int ModelHandle, int frameIndex, MATRIX matDir);// 生成処理.
    const void MakePermitUpdateFalse() { permitUpdate = false; }// permitUpdateをfalseにする.
    void OnCollisionEnter(const ObjectBase* other) override;
    void Draw()override;


private:
    void Delete();// 消す処理.
    ObjectTag myTag;  
    VECTOR velocity;
    const float modelScale = 0.04f;
    const float modelScaleY = 0.008f;
    const float ColRadius = 0.07f;// 弾頭当たり判定半径.[m]
    const float Speed = 444.000f;// 弾速.[m/h]
    const float DeadTime = 3.0f;// 削除時間.
    const float BlastTime = 0.8f;// 爆発半径有効時間.
    const float AccelerationTime = 1.0f;// 加速時間.
    float timeCount;
};

