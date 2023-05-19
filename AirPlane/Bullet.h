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
    void Generate(VECTOR pos, MATRIX matDir);// 生成処理.
    const void MakePermitUpdateFalse() { permitUpdate = false; }// permitUpdateをfalseにする.
    void OnCollisionEnter(const ObjectBase* other) override;
    void Draw()override;


private:
    float CalculateAngle(VECTOR airplanePos, MATRIX airplaneMatDir);// 角度を算出.
    void Delete();// 消す処理.
    ObjectTag myTag;
    VECTOR velocity;
    const float modelScale = 0.004f;
    const float ColRadius = 0.1f;// 当たり判定半径.
    const float Speed = 1050.0f;// 弾速.
    const float DeadTime = 3.0f;
    float timeCount;
    const VECTOR PosCorrectionScale = VGet(-1.2f, 0.0f, -5.0f);// 銃口位置補正定数.
    const float GunTargetingDistance = 800.0f;
};

