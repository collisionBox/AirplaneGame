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
    float CalculateAngle(VECTOR airplanePos, MATRIX airplaneMatDir);// 角度を算出.
    void Delete();// 消す処理.
    ObjectTag myTag;
    VECTOR velocity;
    MATRIX mat;
    MATRIX matRot;
    MATRIX matTrans;
    const float modelScale = 0.04f;
    const float ColRadius = 0.1f;// 当たり判定半径.
    const float Speed = 1050.0f;// 弾速.
    const float DeadTime = 3.0f;
    float timeCount;
    const float DistanceOfCocpitAndPod = 7.473f;
    const float DistanceOfBodyAndPod = 32.49f;
    //const VECTOR PosCorrection =  AssetManager::GetFramePos()// 銃口位置補正.
    const float ZeroInAngle = atanf((GunTargetingDistance + DistanceOfCocpitAndPod)/ DistanceOfBodyAndPod);
};

